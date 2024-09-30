/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:45:10 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/29 17:45:47 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int process_input_her(int tmp_fd, char *quoted_limiter, int flag, char **envp)
{
    char *line;
    char *expanded_line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            return 0;
        expanded_line = handle_expansion(quoted_limiter, line, flag, envp);
        line = expanded_line;
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