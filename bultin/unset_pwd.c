/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:52:44 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/13 17:49:48 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bult_pwd(void)
{
	char	*cwd;
	char *ex;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell");
		ex=manage_exit_status(EXIT_FAILURE, 1); // Set failure status
		free(ex);
		return;
	}
	printf("%s\n", cwd);
	ex=manage_exit_status(EXIT_SUCCESS, 1); // Set success status
	free(ex);
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
	char *ex;

	i = 1;
	if (!cmd->args[i])
	{
		ex=manage_exit_status(1, 1);
		free(ex);
		return ;
	}
	while (cmd->args[i])
	{
		if (unset_variable(env, cmd->args[i]))
		{
			ex=manage_exit_status(0, 1);
			free(ex);
		}
		else
		{
			ex=manage_exit_status(1, 1);
			free(ex);
		}
		i++;
	}
}
