/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:47:43 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/15 17:40:46 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parent_signals(t_command *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	signal(SIGINT, SIG_IGN);
	cmd->ex = manage_exit_status(127, 1);
	free(cmd->ex);
	signal(SIGQUIT, SIG_IGN);
}

char	**handle_builtin_cmd(t_command *cmd, char **envp)
{
	handle_redirects(cmd);
	envp = handle_builtin(cmd, envp);
	return (envp);
}

char	**handle_builtin_cmd_out(t_command *cmd, char **envp)
{
	if(!envp || !(*envp))
		return (NULL);
	
	handle_redirects(cmd);
	envp = handle_built_out(cmd, envp);
	return (envp);
}
