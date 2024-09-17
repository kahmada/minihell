/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:28:18 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/17 15:01:41 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*manage_exit_status(int status, int set_flag)
{
	static int	current_status;

	if (set_flag)
		current_status = status;
	return (ft_itoa(current_status));
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**handle_builtin(t_command *cmd, char **envp)
{
	t_env	*env;

	env = NULL;
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		return (envp);
	env = get_env(&envp, env);
	if (!env)
		return (envp);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		bult_env(env, cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		bult_cd(cmd, &env);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		bult_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		bult_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		bult_pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		bult_unset(cmd, &env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		bult_export(cmd, &env);
	envp = env_to_envp(env);
	free_env(env);
	return (envp);
}
