/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:28:47 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/14 18:40:45 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_vars(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value && tmp->value[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_env_until_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if ((tmp->key) && tmp->value && tmp->value[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	bult_env(t_env *env, t_command *cmd)
{
	if (env == NULL)
	{
		cmd->ex = manage_exit_status(1, 1);
		free(cmd->ex);
		return ;
	}
	if (ft_strcmp(env->key, "PWD") == 0)
	{
		print_env_until_path(env);
		cmd->ex = manage_exit_status(0, 1);
		free(cmd->ex);
	}
	else
	{
		print_env_vars(env);
		cmd->ex = manage_exit_status(0, 1);
		free(cmd->ex);
	}
}
