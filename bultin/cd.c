/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:27:16 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/14 19:52:05 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_envp(t_env **envp, char *key, char *value)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	bult_cd(t_command *cmd, t_env **envp)
{
	char	*path;
	int		ret;
	char	*oldpath;
	char	*new_path;

	oldpath = getenv("PWD");
	if (cmd->args[1] == NULL)
		path = getenv("HOME");
	else
		path = cmd->args[1];
	ret = chdir(path);
	if (ret == -1)
	{
		perror("minishell");
		cmd->ex = manage_exit_status(1, 1);
		free(cmd->ex);
		return ;
	}
	cmd->ex = manage_exit_status(0, 1);
	free(cmd->ex);
	update_envp(envp, "OLDPWD", oldpath);
	new_path = getcwd(NULL, 0);
	update_envp(envp, "PWD", new_path);
	free(new_path);
}
