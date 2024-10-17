/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:20:58 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/17 18:20:30 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_variable_name(char *key)
{
	int	i;

	i = 0;
	if (key[i] == '_')
		i++;
	else if (!key[i] || !ft_isalpha(key[i]))
		return (0);
	i++;
	return (1);
}

t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value && env->value[0])
			printf("=\"%s\"", env->value);
		env = env->next;
		printf("\n");
	}
}

void	update_environment(t_env **env, char *key, char *value)
{
	t_env	*existing;

	existing = find_env(*env, key);
	if (existing)
	{
		free(existing->value);
		existing->value = ft_strdup(value);
	}
	else
		add_env(env, key, value);
}
