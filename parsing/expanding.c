/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 17:16:35 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_exit_status(t_token *token)
{
	char	*expanded;

	if (token->type == EXIT_STATUS)
	{
		expanded = manage_exit_status(0, 0);
		free(token->data);
		token->data = expanded;
	}
}

static void	expand_special_vars(t_token *token)
{
	if (ft_strcmp(token->data, "$*") == 0
		|| ft_strcmp(token->data, "\"$*\"") == 0
		|| ft_strcmp(token->data, "$!") == 0
		|| ft_strcmp(token->data, "\"$!\"") == 0)
	{
		free(token->data);
		token->data = ft_strdup("");
	}
}

int	is_ambiguous_redirect(t_token *token, char *expanded)
{
	t_token	*curr;

	if (ft_strcmp(expanded, "") == 0)
	{
		curr = token->previous;
		while (curr && (curr->type == SPAACE || curr->type == TAAB))
			curr = curr->previous;
		if (curr && (curr->type == REDIRECT_APPEND
				|| curr->type == REDIRECT_IN || curr->type == REDIRECT_OUT))
			return (1);
	}
	return (0);
}

static void	expand_dollar_sign(t_token *token, char **envp)
{
	char	*expanded;

	if (ft_strchr(token->data, '$'))
	{
		expanded = expand_variable(token->data, envp);
		if (!is_ambiguous_redirect(token, expanded))
		{
			free(token->data);
			token->data = expanded;
		}
		else
			free(expanded);
	}
}

void	handle_token_expansion(t_token *token, char **envp)
{
	if (token->data[0] != '\'' && !check_heredoc_presence(token)
		&& token->type != DS)
	{
		expand_exit_status(token);
		expand_special_vars(token);
		expand_home(token);
		if (token->data[0] != '"' && token->data[0] != '\'')
			expand_dollar_sign(token, envp);
		else if (token->data[0] == '"')
			expand_dollar_sign(token, envp);
	}
}
