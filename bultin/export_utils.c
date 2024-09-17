/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:20:58 by kahmada           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/15 19:09:52 by kahmada          ###   ########.fr       */
=======
/*   Updated: 2024/09/12 18:14:57 by kahmada          ###   ########.fr       */
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_variable_name(char *key)
{
	int	i;

	i = 0;
	if (!key[i] || !ft_isalpha(key[i]) || key[i] == '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '-' && key[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env(t_env *env, const char *key)
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
			printf("=\"%s\"\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

void	update_environment(t_env **env, char *key, char *value, int append_mode)
{
	t_env	*existing;

	(void)append_mode;
	existing = find_env(*env, key);
	if (existing)
	{
		free(existing->value);
		existing->value = ft_strdup(value);
	}
	else
	{
		// printf("here again\n");
		add_env(env, key, value);
<<<<<<< HEAD
}
=======
	}
}
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
