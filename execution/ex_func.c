/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:47:43 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/17 17:25:48 by kahmada          ###   ########.fr       */
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
	handle_redirects(cmd);
	envp = handle_built_out(cmd, envp);
	return (envp);
}

void handle_inside_minishel(t_command *cmd)
{
    if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
        return;
    if (cmd->args[0][0] == '.')
    {
        close(0);
		close(1);
    }
}

//        ;