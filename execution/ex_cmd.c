/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:53:32 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/17 15:00:27 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_command_path(char *cmd_path, char *cmd_name)
{
	char	*ex;

	if (!cmd_path)
	{
		if (cmd_name)
			fprintf(stderr, "Command not found: %s\n", cmd_name);
		ex = manage_exit_status(127, 1);
		free(ex);
		exit(127);
	}
	else if (ft_strcmp(cmd_path, "1") == 0 || ft_strcmp(cmd_path, "2") == 0)
		return (1);
	else if (ft_strcmp(cmd_path, "3") == 0)
	{
		printf("%s: No such file or directory\n", cmd_name);
		return (2);
	}
	return (0);
}

void	child_process_execution(t_command *cmd, char **envp, int *input_fd)
{
	char	*cmd_path;
	int		status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(*input_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[0]);
	if (*input_fd != 0)
		close(*input_fd);
	handle_redirects(cmd);
	cmd_path = find_commande(cmd->args[0], envp);
	status = handle_command_path(cmd_path, cmd->args[0]);
	if (status == 1 || status == 2)
		return ;
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
	exit(EXIT_FAILURE);
}

pid_t	execute_piped_cmd(t_command *cmd, char **envp, int *input_fd)
{
	pid_t	pid;

	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe");
		cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
		free(cmd->ex);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		perror("mini: fork");
		cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
		free(cmd->ex);
		exit(EXIT_FAILURE);
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
		if (cmd->next == NULL && is_builtin(cmd->args[0]))
			return ;
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
	if (!cmd)
		return (envp);
	count = count_commands(cmd);
	child_pids = (int *)malloc(sizeof(int) * count);
	exec_pipes(cmd, envp, child_pids, &input_fd);
	if (cmd && is_builtin(cmd->args[0]))
	{
		cmd->last_envp = handle_builtin_cmd(cmd, envp);
		envp = f_update_envp(envp, cmd->last_envp);
	}
	close(input_fd);
	wait_for_children(child_pids, count);
	free(child_pids);
	signal(SIGINT, sigint_handler);
	return (envp);
}
