/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:00:24 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/01 15:29:57 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	wrerror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}
