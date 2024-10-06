/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:28:18 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/06 19:03:29 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**handle_built_out(t_command *cmd, char **envp)
{
	t_env	*env;

	env = NULL;
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		return (envp);
	env = get_env(&envp, env);
	if (!env)
	{
		add_env(&env, "PWD", getcwd(NULL, 0));
		add_env(&env, "SHLVL", "1");
		add_env(&env, "_", "/usr/bin/env");
		add_env(&env, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	}
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		bult_cd(cmd, &env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		bult_unset(cmd, &env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		bult_export(cmd, &env);
	envp = env_to_envp(env);
	free_env(env);
	return (envp);
}

char	**handle_builtin(t_command *cmd, char **envp)
{
	t_env	*env;

	env = NULL;
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		return (envp);
	env = get_env(&envp, env);
	if (!env)
	{
		add_env(&env, "PWD", getcwd(NULL, 0));
		add_env(&env, "SHLVL", "1");
		add_env(&env, "_", "/usr/bin/env");
		add_env(&env, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	}
	if (ft_strcmp(cmd->args[0], "env") == 0)
		bult_env(env, cmd);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		bult_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		bult_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		bult_pwd(cmd);
	envp = env_to_envp(env);
	free_env(env);
	return (envp);
}
