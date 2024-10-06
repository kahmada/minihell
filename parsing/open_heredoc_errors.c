/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:11:25 by chourri           #+#    #+#             */
/*   Updated: 2024/10/06 15:15:22 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	quote_range(char *data, int *start, int *end)
{
	int		len;
	char	opening_quote;

	len = ft_strlen(data);
	*start = 0;
	*end = len - 1;
	if (data[0] == '"' || data[0] == '\'')
	{
		opening_quote = data[0];
		if (data[*end] == opening_quote)
		{
			(*start)++;
			(*end)--;
		}
	}
}

static char	*remove_quotes_limiter_hd(char *data)
{
	int		start;
	int		end;
	int		len;
	char	*new;
	int		i;

	quote_range(data, &start, &end);
	len = end - start + 1;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = data[start + i];
	new[len] = '\0';
	return (new);
}

static int	create_tempfile_error(char *temp_filename, int file_counter)
{
	const char	*base_filename;
	char		*counter_str;
	int			tmp_fd;

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
	{
		perror("open");
		return (-1);
	}
	return (tmp_fd);
}

static void	handle_heredoc_input(int tmp_fd, const char *ql, t_token *lst)
{
	char	*line;
	char	*ex;

	while (1)
	{
		line = readline("> ");
		if (g_sig_received == 1)
		{
			ex = manage_exit_status(1, 1);
			free(ex);
			lst->sig_flag = 1;
			g_sig_received = 0;
			break ;
		}
		if (!line)
			break ;
		if (ft_strcmp(line, ql) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
}

void	handle_child_error(const char *limiter, t_token *lst)
{
	char	*quoted_limiter;
	int		tmp_fd;
	char	temp_filename[256];

	tmp_fd = create_tempfile_error(temp_filename, 0);
	if (tmp_fd == -1)
		return ;
	quoted_limiter = remove_quotes_limiter_hd((char *)limiter);
	if (!quoted_limiter)
	{
		close(tmp_fd);
		unlink(temp_filename);
		return ;
	}
	signal(SIGINT, signal_handler_heredoc);
	handle_heredoc_input(tmp_fd, quoted_limiter, lst);
	free(quoted_limiter);
	close(tmp_fd);
	unlink(temp_filename);
}
