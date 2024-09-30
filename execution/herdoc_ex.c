/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:33:51 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/29 17:44:56 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_process(t_here_doc *here_doc_info)
{
    handle_child(here_doc_info->limiter, here_doc_info->fd, here_doc_info->envp);
    here_doc_info->fd = open(here_doc_info->file_name, O_RDONLY, 0644);
    if (here_doc_info->fd == -1) {
        perror("open");
        return;
    }
    here_doc_info->cmd->fd_in = here_doc_info->fd;
    unlink(here_doc_info->file_name);
}

void handle_here_doc(const char *limiter, t_command *cmd, int file_counter, char **envp)
{
    if (limiter == NULL || cmd == NULL) {
        perror("Invalid arguments");
        return;
    }

    char temp_filename[256];
    int tmp_fd = create_tempfile(temp_filename, file_counter);
    if (tmp_fd == -1)
        return;

    t_here_doc here_doc_info = {limiter, tmp_fd, temp_filename, cmd, envp};

    handle_process(&here_doc_info);
}

int    not_last(t_command *first, int i)
{
    i++;
    while (first->args[i])
    {
        if (ft_strcmp(first->args[i], "<<") == 0 && first->args[i + 1])
            return (1);
        i++;
    }
    return (0);
}
int process_here_doc(t_command *cmd, int i, int *file_counter, char **envp)
{
	int fd = dup(0);
	handle_here_doc(cmd->args[i + 1], cmd, (*file_counter)++, envp);
	if (not_last(cmd, i))
        close(cmd->fd_in); 
	if (sig_received == 1)
	{
		cmd->ex = manage_exit_status(1,1);
		free(cmd->ex);
		dup2(fd, 0);
		close(fd);
		sig_received = 0;
		return (1);
	}
	close(fd);
	return (0);
}

int her(t_command *cmd, char **envp)
{
	t_command *start;
	int file_counter = 0;
	int i;

	if (cmd == NULL)
	{
		perror("Invalid command");
		return (0);
	}
	start = cmd;
	while (start != NULL)
	{
		i = 0;
		while (start->args[i] != NULL && start->args[i + 1])
		{
			if (ft_strcmp(start->args[i], "<<") == 0)
			{
				if (process_here_doc(start, i, &file_counter, envp) == 1)
					return (1);
			}
			i++;
		}
		start = start->next;
	}
	return (0);
}

