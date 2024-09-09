/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:53:32 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/09 18:05:34 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**handle_builtin_cmd(t_command *cmd, char **envp)
{
	char	*ex;
	handle_redirects(cmd);
	envp = handle_builtin(cmd, envp);
	ex = manage_exit_status(0, 1);
	free(ex);
	return (envp);
}

void	child_process_execution(t_command *cmd, char **envp, int *input_fd)
{
	char	*cmd_path;
	char	*ex;
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
	if (!cmd_path)
	{
		if (cmd->args[0])
		{
			fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
			ex = manage_exit_status(127, 1);
			free(ex);
		}
		exit(127);
	}
	else if (ft_strcmp(cmd_path, "1") == 0 || ft_strcmp(cmd_path, "2") == 0)
		return;
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	ex = manage_exit_status(EXIT_FAILURE, 1);
	free(ex);
	exit(EXIT_FAILURE);
}

pid_t	execute_piped_cmd(t_command *cmd, char **envp, int *input_fd)
{
	pid_t	pid;
	char	*ex;
	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe");
		ex = manage_exit_status(EXIT_FAILURE, 1);
		free(ex);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ex = manage_exit_status(EXIT_FAILURE, 1);
		free(ex);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process_execution(cmd, envp, input_fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (pid);
}

void	wait_for_children(int *child_pids, int count)
{
	int	status;
	int	i;
	char	*ex;

	i = -1;
	while (++i < count)
	{
		waitpid(child_pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			if (WIFEXITED(status))
			{
				printf("{%d}\n", WEXITSTATUS(status));
				ex = manage_exit_status(WEXITSTATUS(status), 1);
				free(ex);
			}
			write(1, "Quit: 3\n", 9);
		}
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			ex = manage_exit_status(WEXITSTATUS(status), 1);
			free(ex);
		}
	}
}

char	**execute_cmd(t_command *cmd, char **envp)
{
	int	input_fd;
	int	child_pids[256];
	int	i;

	input_fd = 0;
	i = 0;
	if (!cmd)
		return (envp);
	// if (cmd->args[0][0] == '#')
	// 	return (envp);
	while (cmd)
	{
		if (cmd->next == NULL && is_builtin(cmd->args[0]))
			return (handle_builtin_cmd(cmd, envp));
		child_pids[i++] = execute_piped_cmd(cmd, envp, &input_fd);
		close(cmd->pipe_fd[1]);
		if (input_fd != 0)
			close(input_fd);
		input_fd = cmd->pipe_fd[0];
		cmd = cmd->next;
	}
	wait_for_children(child_pids, i);
	signal(SIGINT, SIGINT_handler);
	return (envp);
}
