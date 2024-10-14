/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:59:58 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/14 13:55:01 by kahmada          ###   ########.fr       */
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

int	ft_count_exit(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		if (ft_strcmp(cmd->args[0], "exit") == 0)
			count++;
		cmd = cmd->next;
	}
	return (count);
}

void	handle_fork_failure(t_command *cmd, int *has_printed_error)
{
	close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	close(STDOUT_FILENO);
	if (!(*has_printed_error))
	{
		ft_putstr_fd("minishell: fork: Resource temporarily\
		unavailable\n", STDERR_FILENO);
		*has_printed_error = 1;
	}
	cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
	free(cmd->ex);
}
