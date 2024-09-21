/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:07:17 by chourri           #+#    #+#             */
/*   Updated: 2024/09/21 11:07:26 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_child(const char *limiter, int tmp_fd, char **envp)
{
	char *line;
	char *quoted_limiter;
	int flag = 0;
	char	*expanded_line;

	if (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\''))
		flag = 1;
	if (limiter[0] == '$' && limiter[1] != '$' && (ft_strchr((char *)limiter, '"') || ft_strchr((char *)limiter, '\'')))
		limiter++; //ADDED
	quoted_limiter = remove_quotes_limiter((char *)limiter);
	printf("quoted_lmiter = %s\n", quoted_limiter);
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
