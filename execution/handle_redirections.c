/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:03:35 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/15 16:59:15 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

void	process_redirect(t_command *cmd, int i)
{
	int	j;

	j = i;
	if (ft_strcmp(cmd->args[i], ">") == 0)
		handle_redirect_out(cmd->args[i + 1]);
	else if (ft_strcmp(cmd->args[i], "<") == 0)
		handle_redirect_in(cmd->args[i + 1]);
	else if (ft_strcmp(cmd->args[i], ">>") == 0)
		handle_redirect_append(cmd->args[i + 1]);
	while (j < count_args(cmd->args) - 2)
	{
		cmd->args[j] = cmd->args[j + 2];
		j++;
	}
	cmd->args[count_args(cmd->args) - 2] = NULL;
}

void	handle_redirects(t_command *cmd)
{
	int	num_args;
	int	i;

	if (!cmd || !cmd->args)
		return ;
	num_args = count_args(cmd->args);
	i = 0;
	while (i < num_args - 1)
	{
		if (ft_strcmp(cmd->args[i], ">") == 0
			|| ft_strcmp(cmd->args[i], "<") == 0
			|| ft_strcmp(cmd->args[i], ">>") == 0)
		{
			free(cmd->args[i]);
			process_redirect(cmd, i);
			num_args = count_args(cmd->args);
			i--;
		}
		i++;
	}
}

void	process_redirect_hero(t_command *cmd, int i)
{
	int	j;

	j = i;
	if (ft_strcmp(cmd->args[i], "<<") == 0 && cmd->args[i + 1])
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	while (j < count_args(cmd->args) - 2)
	{
		cmd->args[j] = cmd->args[j + 2];
		j++;
	}
	cmd->args[count_args(cmd->args) - 2] = NULL;
}

void	handle_hero(t_command *cmd)
{
	int	num_args;
	int	i;

	if (!cmd || !cmd->args)
		return ;
	num_args = count_args(cmd->args);
	i = 0;
	while (i < num_args - 1)
	{
		if (ft_strcmp(cmd->args[i], "<<") == 0)
		{
			process_redirect_hero(cmd, i);
			num_args = count_args(cmd->args);
			i--;
		}
		i++;
	}
}
