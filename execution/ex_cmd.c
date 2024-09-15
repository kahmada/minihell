/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:53:32 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/15 13:40:33 by chourri          ###   ########.fr       */
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
	status = handle_command_path(cmd_path, cmd->args[0]);
	if (status == 1 || status == 2)
		return;
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	ex = manage_exit_status(EXIT_FAILURE, 1);
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
	if (pid < 0)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		perror("mini: fork");
		ex = manage_exit_status(EXIT_FAILURE, 1);
		free(ex);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process_execution(cmd, envp, input_fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		ex = manage_exit_status(127, 1);
		free(ex);
		signal(SIGQUIT, SIG_IGN);
	}
	return (pid);
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
			free(ex); // Free the allocated string after use
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
			{
				write(1, "QUIT: 3\n", 8);
				ex = manage_exit_status(131, 1);
				free(ex); // Free the allocated string after use
			}
			else if (WTERMSIG(status) == SIGINT)
			{
				write(1, "\n", 1);
				ex = manage_exit_status(130, 1);
				free(ex); // Free the allocated string after use
			}
		}
	}
}

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
char **f_update_envp(char **envp, char **last_envp)
{
    if (envp) // Évite de libérer si c'est la même zone mémoire
    {
        free_2d_array(envp);  // libère l'ancien envp
    }
    envp = last_envp;  // affecte la nouvelle valeur
    return (envp);
}

char	**execute_cmd(t_command *cmd, char **envp)
{
	int	input_fd;
	int count;
	int	*child_pids;
	int	i;
	char **last_envp = NULL;

	count = count_commands(cmd);
	child_pids = (int *)malloc(sizeof(int) * count);
	input_fd = 0;
	i = 0;
	if (!cmd)
		return (envp);
	while (cmd)
	{
		if (cmd->next == NULL && is_builtin(cmd->args[0]))
        {
            last_envp = handle_builtin_cmd(cmd, envp);
            free(child_pids);
            envp = f_update_envp(envp, last_envp);
            return envp;
        }
		child_pids[i++] = execute_piped_cmd(cmd, envp, &input_fd);
		close(cmd->pipe_fd[1]);
		if (input_fd != 0)
			close(input_fd);
		input_fd = cmd->pipe_fd[0];
		cmd = cmd->next;
	}
	wait_for_children(child_pids, i);
	free(child_pids);
	signal(SIGINT, sigint_handler);
	return (envp);
}

