/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:31:20 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/14 18:29:15 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	validate_numeric_argument(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1][0] == '-' || cmd->args[1][0] == '+')
		i++;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			if (cmd->count_exit == 1)
				ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			cmd->ex = manage_exit_status(255, 1);
			free(cmd->ex);
			exit(255);
		}
		i++;
	}
}

void	handle_invalid_argument(char *arg)
{
	char	*ex;

	if (arg && (!ft_strcmp(arg, "+")
			|| !ft_strcmp(arg, "-") || arg[0] == '\0'))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ex = manage_exit_status(255, 1);
		free(ex);
		exit(255);
	}
}

void	handle_numeric_error(t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	cmd->ex = manage_exit_status(255, 1);
	free(cmd->ex);
	exit(255);
}

void	bult_exit(t_command *cmd)
{
	handle_invalid_argument(cmd->args[1]);
	if (cmd->args[1] && !just_spaces(cmd->args[1]) && !cmd->args[2])
		cmd->args[1] = ft_strtrim(cmd->args[1], " ");
	if (cmd->args[1])
	{
		validate_numeric_argument(cmd);
		if (cmd->args[2])
		{
			if (cmd->count_exit == 1)
				ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			free(manage_exit_status(1, 1));
			return ;
		}
		if (cmd->args[1] && (ft_atoi(cmd->args[1]) > INT_MAX))
			handle_numeric_error(cmd);
		if (cmd->count_exit == 1)
			ft_putstr_fd("exit\n", 1);
		free(manage_exit_status(ft_atoi(cmd->args[1]), 1));
		exit(ft_atoi(cmd->args[1]));
	}
	if (cmd->count_exit == 1)
		ft_putstr_fd("exit\n", 1);
	free(manage_exit_status(0, 1));
	exit(0);
}
