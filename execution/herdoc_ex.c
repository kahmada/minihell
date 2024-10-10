/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:33:51 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/10 14:29:19 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_process(t_here_doc *heredoc)
{
	handle_child(heredoc->limiter, heredoc->fd, heredoc->envp);
	heredoc->fd = open(heredoc->file_name, O_RDONLY, 0644);
	if (heredoc->fd == -1)
	{
		perror("open");
		return ;
	}
	heredoc->cmd->fd_in = heredoc->fd;
	unlink(heredoc->file_name);
}

static void	heredoc(const char *lim, t_command *cmd, int filecount, char **envp)
{
	char		temp_filename[256];
	int			tmp_fd;
	t_here_doc	here_doc_info;

	if (lim == NULL || cmd == NULL)
		return ;
	tmp_fd = create_tempfile(temp_filename, filecount);
	if (tmp_fd == -1)
		return ;
	here_doc_info.limiter = lim;
	here_doc_info.fd = tmp_fd;
	here_doc_info.file_name = temp_filename;
	here_doc_info.cmd = cmd;
	here_doc_info.envp = envp;
	handle_process(&here_doc_info);
}

int	process_here_doc(t_command *cmd, int i, int *file_counter, char **envp)
{
	int	fd;

	fd = dup(0);
	heredoc(cmd->args[i + 1], cmd, (*file_counter)++, envp);
	if (not_last(cmd, i))
		close(cmd->fd_in);
	if (g_sig_received == 1)
	{
		cmd->ex = manage_exit_status(1, 1);
		free(cmd->ex);
		dup2(fd, 0);
		close(fd);
		g_sig_received = 0;
		return (1);
	}
	close(fd);
	return (0);
}

int	process_args_her(t_command *cmd, int *file_counter, char **envp)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL && cmd->args[i + 1])
	{
		if (ft_strcmp(cmd->args[i], "<<") == 0)
		{
			if (process_here_doc(cmd, i, file_counter, envp) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	her(t_command *cmd, char **envp)
{
	t_command	*start;
	int			file_counter;

	file_counter = 0;
	if (cmd == NULL)
		return (0);
	start = cmd;
	while (start != NULL)
	{
		if (process_args_her(start, &file_counter, envp) == 1)
			return (1);
		start = start->next;
	}
	return (0);
}
