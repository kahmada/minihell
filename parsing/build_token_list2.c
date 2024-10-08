/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_token_list2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:07:13 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 17:16:21 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	determine_token_type(char *token, int *in_quotes)
{
	t_type	type;

	type = determine_redirect_or_special(token);
	if (type != WORD)
		return (type);
	return (determine_quote_type(token, in_quotes));
}

static void	process_token(t_token **lst, char **tokens, int *i)
{
	t_type	type;
	int		in_quotes;

	in_quotes = 0;
	type = determine_token_type(tokens[*i], &in_quotes);
	if (is_combined(tokens, *i))
	{
		handle_combined_tokens(lst, tokens, i);
		return ;
	}
	ft_lstadd_back(lst, ft_lstnew(ft_strdup(tokens[*i]), type));
}

t_token	*build_token_list(char *output)
{
	int		i;
	t_token	*lst;
	char	**tokens;

	i = 0;
	lst = NULL;
	if (!output || !*output)
		return (NULL);
	tokens = ft_split_tokens(output, NON_PRINTABLE_CHAR);
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		process_token(&lst, tokens, &i);
		i++;
	}
	free_word_array(tokens);
	return (lst);
}
