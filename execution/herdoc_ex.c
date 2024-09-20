/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:33:51 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/20 18:55:15 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_here_doc
{
    const char *limiter;
    int fd;
    char *file_name;
    t_command *cmd;
    char **envp;
} t_here_doc;

void signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		sig_received = 1;
		close(0);
		return;
	}
}

static char *remove_quotes_limiter(const char *arg)
{
	int	i;
	int	j;
	char *new_arg;
	char quote_char;
	int in_quotes;

	i = -1;
	j = 0;
	in_quotes = 0;
	new_arg = (char *)malloc(strlen(arg) + 1);
	if (!new_arg) return NULL;
	while (arg[++i])
	{
		if (!in_quotes && (arg[i] == '\'' || arg[i] == '\"'))
		{
			in_quotes = 1;
			quote_char = arg[i];
		}
		else if (in_quotes && arg[i] == quote_char)
			in_quotes = 0;
		else
			new_arg[j++] = arg[i];
	}
	new_arg[j] = '\0';
	return (new_arg);
}
char *handle_expansion(char *line, int flag, char **envp)
{
    char *expanded_line = line;

    if (!flag && (ft_strchr(line, '$') || ft_strchr(line, '~')))
    {
        expanded_line = expand_variable(line, envp);
        free(line);
    }
    return expanded_line;
}

int process_input_her(int tmp_fd, char *quoted_limiter, int flag, char **envp)
{
    char *line;
    char *expanded_line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            return 0;
        expanded_line = handle_expansion(line, flag, envp);
        line = expanded_line;
		printf("line = %s\n", line);
        if (ft_strcmp(line, quoted_limiter) == 0)
        {
            free(line);
            return 1;
        }
        write(tmp_fd, line, ft_strlen(line));
        write(tmp_fd, "\n", 1);
        free(line);
    }
}

void handle_child(const char *limiter, int tmp_fd, char **envp)
{
    char *quoted_limiter;
    int flag = 0;

    if (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\''))
        flag = 1;
    if (limiter[0] == '$' && limiter[1] != '$' && (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\'')))
        limiter++;
    quoted_limiter = remove_quotes_limiter((char *)limiter);
	printf("limiter = %s \n", quoted_limiter);
     signal(SIGINT, signal_handler_heredoc);
    if (!process_input_her(tmp_fd, quoted_limiter, flag, envp))
        free(quoted_limiter);
    close(tmp_fd);
}


int create_tempfile(char *temp_filename, int file_counter)
{
	const char *base_filename;
	char *counter_str;
	int tmp_fd;

	base_filename = "tempfile_";
	counter_str = ft_itoa(file_counter);
	if (!counter_str)
		return (-1);
	ft_strcpy(temp_filename, base_filename);
	ft_strcat(temp_filename, counter_str);
	ft_strcat(temp_filename, ".txt");
	free(counter_str);
	tmp_fd = open(temp_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmp_fd == -1)
		perror("open");
	return (tmp_fd);
}
// void handle_process(const char *limiter, int fd, char *file_name, t_command *cmd, char **envp)
// {
// 		handle_child(limiter, fd, envp);
// 		fd = open(file_name, O_RDONLY, 0644);
// 		if (fd == -1) {
// 			perror("open");
// 			return;
// 		}
// 		cmd->fd_in = fd;
// 		unlink(file_name);
// }

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


// void handle_here_doc(const char *limiter, t_command *cmd, int file_counter, char **envp)
// {
// 	if (limiter == NULL || cmd == NULL) {
// 		perror("Invalid arguments");
// 		return;
// 	}
// 	char temp_filename[256];
// 	int tmp_fd = create_tempfile(temp_filename, file_counter);
// 	if (tmp_fd == -1)
// 		return;
// 	handle_process(limiter, tmp_fd, temp_filename, cmd, envp);
// }

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

