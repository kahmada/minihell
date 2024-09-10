/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:27:16 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/10 17:26:00 by chourri          ###   ########.fr       */
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
// void	bult_cd(t_command *cmd, t_env **envp)
// {
// 	(void)envp;
// 	char	*path;
// 	int		ret;
// 	char	*oldpath;

// 	oldpath = getenv("PWD");
// 	if (cmd->args[1] == NULL)
// 		path = getenv("HOME");
// 	else
// 		path = cmd->args[1];
// 	ret = chdir(path);
// 	if (ret == -1)
// 	{
// 		perror("minishell");
// 		// manage_exit_status(1, 1);
// 		free(path);
// 		free(oldpath);
// 		return ;
// 	}
// 	// manage_exit_status(0, 1);
// 	update_envp(envp, "OLDPWD", oldpath);
// 	update_envp(envp, "PWD", getcwd(NULL, 0));

// 	// printf("%p\n", path);
// 	// printf("%p\n", oldpath);
// }

void	bult_cd(t_command *cmd, t_env **envp)
{
	char	*path;
	int		ret;
	char	*oldpath;
	char	*ex;

	oldpath = getenv("PWD");
	if (cmd->args[1] == NULL)
		path = getenv("HOME"); // getenv result should not be freed
	else
		path = cmd->args[1];

	ret = chdir(path);
	if (ret == -1)
	{
		perror("minishell");
		ex = manage_exit_status(1, 1);
		free(ex);
		return;
	}
	ex = manage_exit_status(0, 1);
	free(ex);
	update_envp(envp, "OLDPWD", oldpath);

	// getcwd allocates memory, so it needs to be freed later
	char *new_path = getcwd(NULL, 0);
	update_envp(envp, "PWD", new_path);
	free(new_path);  // Free only new_path, as it was dynamically allocated by getcwd()
}
