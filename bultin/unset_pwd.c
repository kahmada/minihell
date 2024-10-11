/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:52:44 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/11 18:46:37 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bult_pwd(t_command *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell");
		cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
		free(cmd->ex);
		return ;
	}
	printf("%s\n", cwd);
	cmd->ex = manage_exit_status(EXIT_SUCCESS, 1);
	free(cmd->ex);
	free(cwd);
}

int	unset_variable(t_env **env, const char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	bult_unset(t_command *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
	{
		cmd->ex = manage_exit_status(0, 1);
		free(cmd->ex);
		return ;
	}
	while (cmd->args[i])
	{
		if (!is_valid_variable_name(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(":not a valid identifier\n", 2);
			cmd->ex = manage_exit_status(1, 1);
			free(cmd->ex);
		}
		else if(unset_variable(env, cmd->args[i]))
		{
			cmd->ex = manage_exit_status(0, 1);
			free(cmd->ex);
		}
		i++;
	}
}
