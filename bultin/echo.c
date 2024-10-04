/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:28:35 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/03 18:11:51 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s || fd < 0)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

int	contain_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	bult_echo(t_command *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd->args[i] && contain_n(cmd->args[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	cmd->ex = manage_exit_status(0, 1);
	free(cmd->ex);
}
