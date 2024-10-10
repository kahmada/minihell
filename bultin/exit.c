/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:31:20 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/10 14:10:54 by kahmada          ###   ########.fr       */
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

void	validate_numeric_argument(char *arg)
{
	int		i;
	char	*ex;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd(arg, 2);
			write(2, "\n", 1);
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
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

	if (arg && (!ft_strcmp(arg, "+")
				|| !ft_strcmp(arg, "-")))
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
		validate_numeric_argument(cmd->args[1]);
		if (cmd->args[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			cmd->ex = manage_exit_status(1, 1);
			free(cmd->ex);
			return ;
		}
		if (cmd->args[1] && (ft_atoi(cmd->args[1]) > LONG_MAX))
			handle_numeric_error(cmd);
		ft_putstr_fd("exit\n", 1);
		cmd->ex = manage_exit_status(atoi(cmd->args[1]), 1);
		free(cmd->ex);
		exit(atoi(cmd->args[1]));
	}
	ft_putstr_fd("exit\n", 1);
	cmd->ex = manage_exit_status(0, 1);
	free(cmd->ex);
	exit(0);
}
