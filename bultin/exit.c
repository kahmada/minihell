/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:31:20 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/10 17:25:24 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + start, len);
	trimmed[len] = '\0';
	return (trimmed);
}

int	just_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	validate_numeric_argument(char *arg)
{
	int	i;
	char	*ex;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			fprintf(stderr, "%s\n", arg);
			fprintf(stderr, "exit\n");
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
				arg);
			ex = manage_exit_status(255, 1);
			free(ex);
			exit(255);
		}
		i++;
	}
}

void	handle_invalid_argument(char *arg)
{
	char	*ex;
	if (arg && (arg[0] == '\0' || (!ft_strcmp(arg, "+") || !ft_strcmp(arg, "-"))))
	{
		fprintf(stderr, "exit\n");
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			arg);
		ex = manage_exit_status(255, 1);
		free(ex);
		exit(255);
	}
}

void	bult_exit(t_command *cmd)
{
	char	*ex;
	handle_invalid_argument(cmd->args[1]);
	if (cmd->args[1] && !just_spaces(cmd->args[1]) && !cmd->args[2])
		cmd->args[1] = ft_strtrim(cmd->args[1], " ");
	if (cmd->args[1])
	{
		validate_numeric_argument(cmd->args[1]);
		if (cmd->args[2])
		{
			fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
			ex = manage_exit_status(1, 1);
			free(ex);
			return ;
		}
		if (cmd->args[1] && (ft_atoi(cmd->args[1]) > LONG_MAX))
		{
			fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			ex = manage_exit_status(255, 1);
			free(ex);
			exit(255);
		}
		printf("exit\n");
		ex = manage_exit_status(atoi(cmd->args[1]), 1);
		free(ex);
		exit(atoi(cmd->args[1]));
	}
	printf("exit\n");
	ex = manage_exit_status(0, 1);
	free(ex);
	exit(0);
}
