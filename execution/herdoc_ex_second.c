/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_ex_second.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:42:36 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/14 14:54:00 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		rl_catch_signals = 0;
		g_sig_received = 1;
		close(0);
		return ;
	}
}

char	*remove_quotes_limiter(const char *arg)
{
	int		i;
	int		j;
	char	*new_arg;
	char	quote;

	i = 0;
	j = 0;
	new_arg = (char *)malloc(ft_strlen(arg) + 1);
	if (!new_arg)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote = arg[i++];
			while (arg[i] && arg[i] != quote)
				new_arg[j++] = arg[i++];
		}
		else
			new_arg[j++] = arg[i++];
	}
	new_arg[j] = '\0';
	return (new_arg);
}

void	ft_remove_quotes(char **str)
{
	char	*src;
	char	*dst;
	char	*dst_start;

	src = *str;
	dst = (char *)malloc(ft_strlen(src) + 1);
	if (dst == NULL)
	{
		perror("malloc");
		return ;
	}
	dst_start = dst;
	while (*src != '\0')
	{
		if (*src != '\'' && *src != '\"')
		{
			*dst++ = *src;
		}
		src++;
	}
	*dst = '\0';
	free(*str);
	*str = dst_start;
}

char	*handle_exp(char *limiter, char *line, int flag, char **envp)
{
	char	*expanded_line;

	expanded_line = line;
	if (!flag && (ft_strchr(line, '$')
			|| ft_strchr(line, '~')) && ft_strcmp(limiter, line))
	{
		expanded_line = expand_variable(line, envp);
		free(line);
	}
	return (expanded_line);
}
