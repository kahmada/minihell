/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:53:28 by chourri           #+#    #+#             */
/*   Updated: 2024/10/02 12:13:14 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand(t_token *token, char **envp)
{
	while (token && token->data)
	{
		if (token->previous)
		{
			if ((token->previous->type == REDIRECT_IN || token->previous->type == REDIRECT_OUT || token->previous->type == REDIRECT_APPEND) && token->data[0] == '$' && !expand_variable(token->data, envp) && token->next)
				token = token->next;
		}
		else
			handle_token_expansion(token, envp);
		token = token->next;
	}
}

