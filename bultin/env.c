/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:28:47 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/14 19:56:16 by kahmada          ###   ########.fr       */
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

char	*create_env_string(t_env *env)
{
	int		var_len;
	int		value_len;
	char	*env_str;

	var_len = ft_strlen(env->key);
	value_len = 0;
	if (env->value != NULL)
		value_len = ft_strlen(env->value);
	env_str = (char *)malloc((var_len + value_len + 2) * sizeof(char));
	if (!env_str)
		return (NULL);
	strcpy(env_str, env->key);
	strcat(env_str, "=");
	if (env->value)
		strcat(env_str, env->value);
	return (env_str);
}

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		i;
	int		count;

	count = count_env_vars(env);
	envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = create_env_string(tmp);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
