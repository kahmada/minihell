/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:53:32 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/14 14:07:33 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_command_path(char *cmd_path, char *cmd_name)
{
	char	*ex;

	if (!cmd_path)
	{
		if (cmd_name)
		{
			ft_putstr_fd("Command not found: ", 2);
			ft_putstr_fd(cmd_name, 2);
			write(2, "\n", 1);
			ex = manage_exit_status(127, 1);
			free(ex);
			exit(127);
		}
		ex = manage_exit_status(0, 1);
		free(ex);
		exit(0);
	}
	else if (ft_strcmp(cmd_path, "1") == 0 || ft_strcmp(cmd_path, "3") == 0)
		exit(126);
	else if (ft_strcmp(cmd_path, "2") == 0)
		exit(127);
}

void	child_process_execution(t_command *cmd, char **envp, int *input_fd)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(*input_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[0]);
	if (*input_fd != 0)
		close(*input_fd);
	handle_redirects(cmd);
	handle_hero(cmd);
	if (is_builtin(cmd->args[0]))
	{
		cmd->last_envp = handle_builtin_cmd(cmd, envp);
		envp = f_update_envp(envp, cmd->last_envp);
		exit(0);
	}
	cmd_path = find_commande(cmd->args[0], envp);
	handle_command_path(cmd_path, cmd->args[0]);
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

pid_t	execute_piped_cmd(t_command *cmd, char **envp, int *input_fd)
{
	pid_t		pid;
	static int	has_printed_error;

	has_printed_error = 0;
	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe");
		cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
		free(cmd->ex);
	}
	pid = fork();
	if (pid < 0)
	{
		handle_fork_failure(cmd, &has_printed_error);
		return (0);
	}
	else if (pid == 0)
		child_process_execution(cmd, envp, input_fd);
	else
		handle_parent_signals(cmd);
	return (pid);
}

void	exec_pipes(t_command *cmd, char **envp, int *child_pids, int *input_fd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		child_pids[i++] = execute_piped_cmd(cmd, envp, input_fd);
		close(cmd->pipe_fd[1]);
		if (*input_fd != 0)
			close(*input_fd);
		*input_fd = cmd->pipe_fd[0];
		cmd = cmd->next;
	}
}

char	**execute_cmd(t_command *cmd, char **envp)
{
	int	input_fd;
	int	count;
	int	*child_pids;

	input_fd = 0;
	cmd->count_exit = ft_count_exit(cmd);
	if (!cmd)
		return (envp);
	count = count_commands(cmd);
	child_pids = (int *)malloc(sizeof(int) * count);
	if ((ft_strcmp(cmd->args[0], "exit") == 0 && cmd->next == NULL))
		return (free(child_pids), handle_exit(cmd, envp));
	if (cmd && is_builtin_out(cmd->args[0]) && cmd->next == NULL)
	{
		cmd->last_envp = handle_builtin_cmd_out(cmd, envp);
		envp = f_update_envp(envp, cmd->last_envp);
		return (free(child_pids), envp);
	}
	exec_pipes(cmd, envp, child_pids, &input_fd);
	close(input_fd);
	wait_for_children(child_pids, count);
	free(child_pids);
	signal(SIGINT, sigint_handler);
	return (envp);
}
