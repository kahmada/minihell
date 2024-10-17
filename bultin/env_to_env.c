/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:34:37 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/17 18:20:50 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ft_strcpy(env_str, env->key);
	ft_strcat(env_str, "=");
	if (env->value)
		ft_strcat(env_str, env->value);
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
			return (free(envp), NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
