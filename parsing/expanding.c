/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/09/14 11:11:35 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand(t_token *token, char **envp)
{
	char	*var_name;
	char	*expanded;
	(void)envp;
	while (token && token->data)
	{
		if (token && token->data && token->data[0] != '\'' && !check_heredoc_presence(token) && token->type != DS)
		{
			if (token->data && token->type == EXIT_STATUS)
			{
				expanded = manage_exit_status(0, 0);
				free(token->data);
				token->data = expanded;
			}
			else if (((token->data[0] == '~' && token->data[1] == '/') || (token->data[0] == '~' && token->data[1] == '\0')) && token->type != EXIT_STATUS)
			{
				expanded = expand_variable(token->data, envp);
				free(token->data);
				token->data = expanded;
			}
			else if ((ft_strcmp(token->data,"$*") == 0 || ft_strcmp(token->data, "\"$*\"") == 0 || ft_strcmp(token->data, "$!") == 0 || ft_strcmp(token->data, "\"$!\"") == 0) && token->data[0] != '\'' && token->type != EXIT_STATUS)
			{
				free(token->data);
				token->data = strdup("\n");
			}
			else if (token->data[0] != '"' && ft_strchr(token->data, '$') && token->type != EXIT_STATUS && token->data[0] != '\'')
			{
				expanded = expand_variable(token->data, envp);
				free(token->data);
				token->data = expanded;
			}
			else if (token->data[0] == '"' && ft_strchr(token->data, '$') && token->type != EXIT_STATUS)
			{
				var_name = ft_strdup(token->data);
				free(token->data);
				token->data = var_name;
				expanded = expand_variable(token->data, envp);
				free(token->data);
				token->data = expanded;
			}
		}
			if (token)
				token = token->next;
	}
}











//to handle
//echo $""
