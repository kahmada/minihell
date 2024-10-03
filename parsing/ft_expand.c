/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:53:28 by chourri           #+#    #+#             */
/*   Updated: 2024/10/03 15:48:09 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand(t_token *token, char **envp)
{
	t_token	*curr;
	char	*expanded;

	while (token && token->data)
	{
		curr = token;
		expanded = expand_variable(curr->data, envp);
		if (curr->previous && curr->data[0] == '$'
			&& ft_strcmp(expanded, "") == 0)
		{
			curr = curr->previous;
			while (curr && (curr->type == SPAACE || curr->type == TAAB))
				curr = curr->previous;
			if ((curr->type == REDIRECT_IN || curr->type == REDIRECT_OUT
					|| curr->type == REDIRECT_APPEND) && curr->next)
				token = token->next;
		}
		else
		{
			handle_token_expansion(token, envp);
			token = token->next;
		}
		free(expanded);
	}
}
