/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_ex_second.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:42:36 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/29 17:51:14 by kahmada          ###   ########.fr       */
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

char *remove_quotes_limiter(const char *arg)
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
char *handle_expansion(char *quoted_limiter, char *line, int flag, char **envp)
{
    char *expanded_line = line;

    if (!flag && (ft_strchr(line, '$') || ft_strchr(line, '~')) && ft_strcmp(quoted_limiter, line))
    {
        expanded_line = expand_variable(line, envp);
        free(line);
    }
    return expanded_line;
}