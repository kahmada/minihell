/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:59:58 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/11 09:44:54 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**f_update_envp(char **envp, char **last_envp)
{
	if (envp)
		free_2d_array(envp);
	envp = last_envp;
	return (envp);
}

void	handle_signal_termination(int status)
{
	char	*ex;

	if (WTERMSIG(status) == SIGQUIT)
	{
		ex = manage_exit_status(131, 1);
		free(ex);
	}
	else if (WTERMSIG(status) == SIGINT)
	{
		ex = manage_exit_status(130, 1);
		free(ex);
	}
}

void	wait_for_children(int *child_pids, int count)
{
	int		status;
	int		i;
	char	*ex;

	i = -1;
	while (++i < count)
	{
		waitpid(child_pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			ex = manage_exit_status(WEXITSTATUS(status), 1);
			free(ex);
		}
		else if (WIFSIGNALED(status))
			handle_signal_termination(status);
	}
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
}
