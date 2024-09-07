/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:16:06 by chourri           #+#    #+#             */
/*   Updated: 2024/09/06 15:35:53 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void add_token_to_list(char *token, t_token **lst)
// {
// 	if (ft_strcmp(token, "<") == 0)
// 		ft_lstadd_back(lst, REDIRECT_IN, token);
// 	else if (ft_strcmp(token, ">") == 0)
// 		ft_lstadd_back(lst, REDIRECT_OUT, token);
// 	else if (ft_strcmp(token, "|") == 0)
// 		ft_lstadd_back(lst, PIPE, token);
// 	else if (ft_strcmp(token, ">>") == 0)
// 		ft_lstadd_back(lst, REDIRECT_APPEND, token);
// 	else if (ft_strcmp(token, "<<") == 0)
// 		ft_lstadd_back(lst, HEREDOC, token);
// 	else if (ft_strcmp(token, "$") == 0)
// 		ft_lstadd_back(lst, DS, token);
// 	else if (token[0] == '\'')
// 		ft_lstadd_back(lst, INSIDE_SINGLE_QUOTE, token);
// 	else if (token[0] == '\"')
// 		ft_lstadd_back(lst, INSIDE_DOUBLE_QUOTE, token);
// 	else if (ft_strcmp(token, "$?") == 0)
// 		ft_lstadd_back(lst, EXIT_STATUS, token);
// 	else if (ft_strcmp(token, " ") == 0)
// 		ft_lstadd_back(lst, SPAACE, token);
// 	else if (ft_strcmp(token, "\t") == 0)
// 		ft_lstadd_back(lst, TAAB, token);
// 	else
// 		ft_lstadd_back(lst, WORD, token);
// }

// void handle_combined_tokens(char **tokens, int *i, t_token **lst)
// {
// 	char	*combined = NULL;
// 	int		j;

// 	combined = strdup(tokens[*i]);
// 	j = *i + 1;
// 	while (tokens[j] && tokens[j][0] == '$' && is_alphabet(tokens[j][1]))
// 	{
// 		char *temp = combined;
// 		combined = ft_strjoin(combined, tokens[j]);
// 		if (!combined)
// 		{
// 			free(temp);
// 			return;
// 		}
// 		free(temp);
// 		j++;
// 	}
// 	// printf("combined ---->%s\n", combined);
// 	ft_lstadd_back(lst, WORD, combined);
// 	*i = j - 1;
// }


// t_token* build_token_list(char *output)
// {
// 	int		i;
// 	t_token	*lst;
// 	char	**tokens;
// 	char	*token_copy;

// 	i = 0;
// 	lst = NULL;
// 	if (!output || !strlen(output))
// 		return NULL;

// 	tokens = ft_split_tokens(output, NON_PRINTABLE_CHAR);

// 	while (tokens[i])
// 	{
// 		token_copy = strdup(tokens[i]);
// 		if (!token_copy)
// 		{
// 			free_word_array(tokens);
// 			free_token_list(lst);
// 			return NULL;
// 		}

// 		if (token_copy[0] == '$' && is_alphabet(token_copy[1]))
// 			handle_combined_tokens(tokens, &i, &lst);
// 		else
// 			add_token_to_list(token_copy, &lst);
// 		i++;
// 	}
// 	// free(token_copy);
// 	free_word_array(tokens);
// 	return lst;
// }



//correct one
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
		t_type type;
		int in_quotes = 0;
		if (ft_strcmp(tokens[i], "<") == 0)
			type = REDIRECT_IN;
		else if (ft_strcmp(tokens[i], ">") == 0)
			type = REDIRECT_OUT;
		else if (ft_strcmp(tokens[i], "|") == 0)
			type = PIPE;
		else if (ft_strcmp(tokens[i], ">>") == 0)
			type = REDIRECT_APPEND;
		else if (ft_strcmp(tokens[i], "<<") == 0)
			type = HEREDOC;
		else if (ft_strcmp(tokens[i], "$") == 0)
			type = DS;
		else if (tokens[i][0] == '\'')
		{
			type = INSIDE_SINGLE_QUOTE;
			in_quotes = 1;
		}
		else if (tokens[i][0] == '\"')
		{
			type = INSIDE_DOUBLE_QUOTE;
			in_quotes = 1;
		}
		else if (ft_strcmp(tokens[i], "$?") == 0)
			type = EXIT_STATUS;
		else if (ft_strcmp(tokens[i], " ") == 0)
			type = SPAACE;
		else if (ft_strcmp(tokens[i], "\t") == 0)
			type = TAAB;
		else if (tokens[i][0] == '$' && is_alphabet(tokens[i][1]))
		{
			char *combined = NULL;
			while (tokens[i] && tokens[i][0] == '$' && is_alphabet(tokens[i][1]))
			{
				char *temp = combined;
				if (!combined)
					combined = ft_strjoin("", tokens[i]);
				else
					combined = ft_strjoin(combined, tokens[i]);
				free(temp);
				i++;
			}
			ft_lstadd_back(&lst, WORD, strdup(combined));
			free(combined);
			continue;
		}
		else
			type = WORD;
		ft_lstadd_back(&lst, type, strdup(tokens[i]));
		if (lst)
		{
			t_token *last = lst;
			while (last->next)
				last = last->next;
			last->in_quotes = in_quotes;
		}
		i++;
	}
	free_word_array(tokens);
	return lst;
}



// t_token* build_token_list(char *output)
// {
// 	int		i;
// 	t_token	*lst;
// 	char	**tokens;
// 	char	*token_copy;

// 	i = 0;
// 	lst = NULL;
// 	if (!output || !strlen(output))
// 		return NULL;

// 	tokens = ft_split_tokens(output, NON_PRINTABLE_CHAR);

// 	while (tokens[i])
// 	{
// 		token_copy = strdup(tokens[i]);
// 		if (!token_copy)
// 		{
// 			free_word_array(tokens);
// 			free_token_list(lst);
// 			return NULL;
// 		}

// 		if (token_copy[0] == '$' && is_alphabet(token_copy[1]))
// 		{
// 			//DO STH
// 		}
// 		else
// 			add_token_to_list(token_copy, &lst);

// 		i++;
// 	}

// 	free_word_array(tokens);
// 	return lst;
// }




// t_token *build_token_list(char *output)
// {
// 	int	 i;
// 	t_token *lst;
// 	char	**tokens;
// 	char	*token_copy;
// 	char	*combined_token;

// 	i = 0;
// 	lst = NULL;
// 	if (!output || !strlen(output))
// 		return lst;

// 	tokens = ft_split_tokens(output, NON_PRINTABLE_CHAR);

// 	while (tokens[i])
// 	{
// 		token_copy = strdup(tokens[i]);
// 		if (!token_copy)
// 		{
// 			free_word_array(tokens);
// 			free_token_list(lst);
// 			return lst;
// 		}

// 		if (token_copy[0] == '$' && is_alphabet(token_copy[1]))
// 		{
// 			combined_token = strdup(token_copy);
// 			// free(token_copy);

// 			while (tokens[i + 1] && tokens[i + 1][0] == '$' && is_alphabet(tokens[i + 1][1]))
// 			{
// 				i++;
// 				char *temp = combined_token;
// 				combined_token = ft_strjoin(temp, tokens[i]);
// 				free(temp);
// 			}

// 			add_token_to_list(combined_token, &lst);
// 			// free(combined_token);
// 		}
// 		else
// 		{
// 			add_token_to_list(token_copy, &lst);
// 			// free(token_copy);
// 		}

// 		i++;
// 	}

// 	free_word_array(tokens);
// 	return lst;
// }


