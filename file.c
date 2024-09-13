/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:19:44 by chourri           #+#    #+#             */
/*   Updated: 2024/09/08 16:32:41 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_combined_token(char **tokens, int i)
{
	return tokens[i][0] == '$' && is_alphabet(tokens[i][1]);
}

void update_last_token_quotes(t_token *lst, int in_quotes)
{
	if (lst)
	{
		t_token *last = lst;
		while (last->next)
			last = last->next;
		last->in_quotes = in_quotes;
	}
}

void handle_combined_tokens(t_token **lst, char **tokens, int *i)
{
	char *combined = NULL;

	while (tokens[*i] && tokens[*i][0] == '$' && is_alphabet(tokens[*i][1]))
	{
		char *temp = combined;
		if (!combined)
			combined = ft_strjoin("", tokens[*i]);
		else
			combined = ft_strjoin(combined, tokens[*i]);
		free(temp);
		(*i)++;
	}

	ft_lstadd_back(lst, WORD, strdup(combined));
	free(combined);
	(*i)--;
}
t_type determine_redirect_or_special(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return REDIRECT_IN;
	else if (ft_strcmp(token, ">") == 0)
		return REDIRECT_OUT;
	else if (ft_strcmp(token, "|") == 0)
		return PIPE;
	else if (ft_strcmp(token, ">>") == 0)
		return REDIRECT_APPEND;
	else if (ft_strcmp(token, "<<") == 0)
		return HEREDOC;
	else if (ft_strcmp(token, "$") == 0)
		return DS;
	else if (ft_strcmp(token, "$?") == 0)
		return EXIT_STATUS;
	else if (ft_strcmp(token, " ") == 0)
		return SPAACE;
	else if (ft_strcmp(token, "\t") == 0)
		return TAAB;

	return WORD;
}
t_type determine_quote_type(char *token, int *in_quotes)
{
	if (token[0] == '\'')
	{
		*in_quotes = 1;
		return INSIDE_SINGLE_QUOTE;
	}
	else if (token[0] == '\"')
	{
		*in_quotes = 1;
		return INSIDE_DOUBLE_QUOTE;
	}

	return WORD;
}

t_type determine_token_type(char *token, int *in_quotes)
{
	t_type type = determine_redirect_or_special(token);
	if (type != WORD)
		return type;
	return determine_quote_type(token, in_quotes);
}

void process_token(t_token **lst, char **tokens, int *i)
{
	t_type type;
	int in_quotes = 0;

	type = determine_token_type(tokens[*i], &in_quotes);

	if (is_combined_token(tokens, *i))
	{
		handle_combined_tokens(lst, tokens, i);
		return;
	}

	ft_lstadd_back(lst, type, strdup(tokens[*i]));
	update_last_token_quotes(*lst, in_quotes);
}


t_token* build_token_list(char *output)
{
	int i = 0;
	t_token *lst = NULL;
	char **tokens;

	if (!output || !*output)
		return NULL;

	tokens = ft_split_tokens(output, NON_PRINTABLE_CHAR);
	if (!tokens)
		return NULL;

	while (tokens[i])
	{
		process_token(&lst, tokens, &i);
		i++;
	}
	free_word_array(tokens);
	return lst;
}
