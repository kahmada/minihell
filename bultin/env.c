/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:28:47 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/29 17:34:19 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bult_env(t_env *env, t_command *cmd)
{
	t_env	*tmp;

	if (env == NULL)
	{
		cmd->ex = manage_exit_status(1, 1);
		free(cmd->ex);
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value && tmp->value[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	cmd->ex = manage_exit_status(0, 1);
	free(cmd->ex);
}
