/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:33:51 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/15 11:24:27 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		sig_received = 1;
		close(0);
		return;
	}
}

static char *remove_quotes2(char *data)
{
	int len = ft_strlen(data);
	int start = 0;
	int end = len - 1;
	char *new;

	if (data[0] == '"' || data[0] == '\'')
	{
		char opening_quote = data[0];
		if (data[end] == opening_quote)
		{
			start++;
			end--;
		}
	}
	len = end - start + 1;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	int i = 0;
	while (i < len)
	{
		new[i] = data[start + i];
		i++;
	}
	new[len] = '\0';
	return (new);
}

void handle_child(const char *limiter, int tmp_fd, char **envp)
{
	char *line;
	char *quoted_limiter;
	int flag = 0;
	char	*expanded_line;

	if (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\''))
		flag = 1;
	quoted_limiter = remove_quotes2((char *)limiter);
	signal(SIGINT, signal_handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			free(quoted_limiter);
			break;
		}
		if (!flag && (ft_strchr(line, '$') || ft_strchr(line, '~')) && ft_strcmp(quoted_limiter, line))
		{
			expanded_line = expand_variable(line, envp);
			free(line);
			line = expanded_line;
		}
		if (ft_strcmp(line, quoted_limiter) == 0)
		{
			free(line);
			free(quoted_limiter);
			close(tmp_fd);
			return ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
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
void handle_process(const char *limiter, int fd, char *file_name, t_command *cmd, char **envp)
{
		handle_child(limiter, fd, envp);
		fd = open(file_name, O_RDONLY, 0644);
		if (fd == -1) {
			perror("open");
			return;
		}
		cmd->fd_in = fd;
		unlink(file_name);
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
	handle_process(limiter, tmp_fd, temp_filename, cmd, envp);
}
int her(t_command *cmd, char **envp)
{
	t_command *start;
	int file_counter;
	int i;
	char	*ex;

	file_counter = 0;
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
				int fd = dup(0);
				handle_here_doc(start->args[i + 1], start, file_counter++, envp);
				if (sig_received == 1)
				{
					ex = manage_exit_status(1,1); //added
					free(ex);
					dup2(fd, 0);
					close(fd);
					sig_received = 0;
					return(1);
				}
			}
			i++;
		}
		start = start->next;
	}
	return(0);
}




// static int sig_received = 0;

// void signal_handler(int signal)
// {
//     if (signal == SIGINT)
// 	{
//         sig_received = 1;// Set flag to indicate signal received
// 		close(0);
// 		return;
//     }
// }

// static char *remove_quotes(char *data)
// {
// 	int len = ft_strlen(data);
// 	int start = 0;
// 	int end = len - 1;
// 	char *new;

// 	if (data[0] == '"' || data[0] == '\'')
// 	{
// 		char opening_quote = data[0];
// 		if (data[end] == opening_quote)
// 		{
// 			start++;
// 			end--;
// 		}
// 	}
// 	len = end - start + 1;
// 	new = malloc(len + 1);
// 	if (!new)
// 		return (NULL);
// 	int i = 0;
// 	while (i < len)
// 	{
// 		new[i] = data[start + i];
// 		i++;
// 	}
// 	new[len] = '\0';
// 	return (new);
// }
// // void handle_child(const char *limiter, int tmp_fd, char **envp) {
// //     char *line;

// //     if (limiter == NULL) {
// //         perror("Invalid limiter");
// //         return;
// //     }
// // 	int flag = 0;
// // 	if (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\''))
// // 		flag = 1;
// // 	limiter = remove_quotes((char *)limiter);
// //     // Setup signal handling
// //     struct sigaction sa;
// //     sa.sa_handler = signal_handler;
// //     sigemptyset(&sa.sa_mask);
// //     sa.sa_flags = 0;
// //     sigaction(SIGINT, &sa, NULL); // Handle SIGINT with signal_handler

// //     while (1) {
// //         if (sig_received) {
// //             write(1, "\n", 1);
// //             exit(1); // Exit the heredoc on Ctrl+C
// //         }

// //         line = readline("> ");
// //         if (line == NULL)
// //             break;
// // 		if (!flag && (ft_strchr(line, '$') || ft_strchr(line, '~')))
// // 			line = expand_variable(line, envp);
// // 		else if (strcmp(line, limiter) == 0)
// // 		{
// //             free(line);
// //             exit(0);
// //         }
// //         write(tmp_fd, line, strlen(line));
// //         write(tmp_fd, "\n", 1);
// //         free(line);
// //     }
// //     close(tmp_fd);
// //     exit(0);
// // }

// //new
// // void handle_child(const char *limiter, int tmp_fd, char **envp) {
// //     char *line;

// //     int flag = 0;
// //     if (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\''))
// //         flag = 1;
// //     limiter = remove_quotes((char *)limiter);
// //     signal(SIGINT, signal_handler);
// //     while (1) {
// //         line = readline("> ");
// //         if (line == NULL)
// //             break;
// //         if (!flag  && (ft_strchr(line, '$') || ft_strchr(line, '~')))
// //         	line = expand_variable(line, envp);
// //         else if (ft_strcmp(line, limiter) == 0) {
// //             free(line);
// //             close(tmp_fd);
// // 			return ;
// //         }
// //         write(tmp_fd, line, strlen(line));
// //         write(tmp_fd, "\n", 1);
// //         free(line);
// //     }
// //     close(tmp_fd);
// // }

// void handle_child(const char *limiter, int tmp_fd, char **envp) {
// 	char *line;
// 	char *quoted_limiter = remove_quotes((char *)limiter);
// 	int flag = 0;

// 	if (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\''))
// 		flag = 1;

// 	signal(SIGINT, signal_handler);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL)
// 			break;
// 		if (!flag && (ft_strchr(line, '$') || ft_strchr(line, '~')))
// 			line = expand_variable(line, envp);
// 		else if (ft_strcmp(line, quoted_limiter) == 0) {
// 			free(line);
// 			free(quoted_limiter);
// 			close(tmp_fd);
// 			return ;
// 		}
// 		write(tmp_fd, line, strlen(line));
// 		write(tmp_fd, "\n", 1);
// 		free(line);
// 	}
// 	free(quoted_limiter);
// 	close(tmp_fd);
// }

// int create_tempfile(char *temp_filename, int file_counter)
// {
//     const char *base_filename;
//     char *counter_str;
//     int tmp_fd;

//     base_filename = "tempfile_";
//     counter_str = ft_itoa(file_counter);
//     if (!counter_str)
//         return (-1);
//     ft_strcpy(temp_filename, base_filename);
//     ft_strcat(temp_filename, counter_str);
//     ft_strcat(temp_filename, ".txt");
//     free(counter_str);
//     tmp_fd = open(temp_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
//     if (tmp_fd == -1)
//         perror("open");

//     return (tmp_fd);
// }
// void handle_process(const char *limiter, int fd, char *file_name, t_command *cmd, char **envp)
// {
//         handle_child(limiter, fd, envp);
//         fd = open(file_name, O_RDONLY, 0644);
//         if (fd == -1) {
//             perror("open");
//             return;
//         }

//         cmd->fd_in = fd;

//         unlink(file_name);
// }

// void handle_here_doc(const char *limiter, t_command *cmd, int file_counter, char **envp) {
//     if (limiter == NULL || cmd == NULL) {
//         perror("Invalid arguments");
//         return;
//     }
//     char temp_filename[256];
//     int tmp_fd = create_tempfile(temp_filename, file_counter);
//     if (tmp_fd == -1)
//         return;
//     handle_process(limiter, tmp_fd, temp_filename, cmd, envp);
// }
// int her(t_command *cmd, char **envp)
// {
//     t_command *start;
//     int file_counter;
//     int i;

//     file_counter = 0;
//     if (cmd == NULL)
//     {
//         perror("Invalid command");
//         return (0);
//     }
//     start = cmd;
//     while (start != NULL)
//     {
//         i = 0;
//         while (start->args[i] != NULL && start->args[i + 1])
//         {
//             if (ft_strcmp(start->args[i], "<<") == 0)
// 			{
// 				int fd = dup(0);
//                 handle_here_doc(start->args[i + 1], start, file_counter++, envp);
// 				if (sig_received == 1)
// 				{
// 					dup2(fd, 0);
// 					close(fd);
// 					sig_received = 0;
// 					return(1);
// 				}
// 			}
//             i++;
//         }
//         start = start->next;
//     }
// 	return(0);
// }
