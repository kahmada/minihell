/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/09/17 12:38:14 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_exit_status(t_token *token)
{
	char	*expanded;

	if (token->type == EXIT_STATUS)
	{
		expanded = manage_exit_status(0, 0);
		free(token->data);
		token->data = expanded;
	}
}

void	expand_tilde(t_token *token, char **envp)
{
	char	*expanded;

	if ((token->data[0] == '~' && token->data[1] == '/')
		|| (token->data[0] == '~' && token->data[1] == '\0'))
	{
		expanded = expand_variable(token->data, envp);
		free(token->data);
		token->data = expanded;
	}
}

void	expand_special_vars(t_token *token)
{
	if (ft_strcmp(token->data, "$*") == 0
		|| ft_strcmp(token->data, "\"$*\"") == 0
		|| ft_strcmp(token->data, "$!") == 0
		|| ft_strcmp(token->data, "\"$!\"") == 0)
	{
		free(token->data);
		token->data = strdup("\n");
	}
}

void	expand_dollar_sign(t_token *token, char **envp)
{
	char	*expanded;

	if (ft_strchr(token->data, '$'))
	{
		expanded = expand_variable(token->data, envp);
		free(token->data);
		token->data = expanded;
	}
}

void	handle_token_expansion(t_token *token, char **envp)
{
	if (token->data[0] != '\'' && !check_heredoc_presence(token)
		&& token->type != DS)
	{
		expand_exit_status(token);
		expand_tilde(token, envp);
		expand_special_vars(token);
		if (token->data[0] != '"' && token->data[0] != '\'')
			expand_dollar_sign(token, envp);
		else if (token->data[0] == '"')
			expand_dollar_sign(token, envp);
	}
}
