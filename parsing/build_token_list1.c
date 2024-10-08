/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_token_list1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:16:06 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 17:15:45 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_combined(char **tokens, int i)
{
	return (tokens[i][0] == '$' && is_alphabet(tokens[i][1]));
}

void	handle_combined_tokens(t_token **lst, char **tokens, int *i)
{
	char	*combined;
	char	*temp;

	combined = NULL;
	while (tokens[*i] && tokens[*i][0] == '$' && is_alphabet(tokens[*i][1]))
	{
		temp = combined;
		if (!combined)
			combined = ft_strjoin("", tokens[*i]);
		else
			combined = ft_strjoin(combined, tokens[*i]);
		free(temp);
		(*i)++;
	}
	ft_lstadd_back(lst, ft_lstnew(ft_strdup(combined), WORD));
	free(combined);
	(*i)--;
}

t_type	determine_redirect_or_special(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, "$") == 0)
		return (DS);
	else if (ft_strcmp(token, "$?") == 0)
		return (EXIT_STATUS);
	else if (ft_strcmp(token, " ") == 0)
		return (SPAACE);
	else if (ft_strcmp(token, "\t") == 0)
		return (TAAB);
	return (WORD);
}

t_type	determine_quote_type(char *token, int *in_quotes)
{
	if (token[0] == '\'')
	{
		*in_quotes = 1;
		return (INSIDE_SINGLE_QUOTE);
	}
	else if (token[0] == '\"')
	{
		*in_quotes = 1;
		return (INSIDE_DOUBLE_QUOTE);
	}
	return (WORD);
}
