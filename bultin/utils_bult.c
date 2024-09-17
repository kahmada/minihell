/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:38:03 by kahmada           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/15 19:23:48 by kahmada          ###   ########.fr       */
=======
/*   Updated: 2024/09/12 18:17:11 by kahmada          ###   ########.fr       */
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
int	set_env_value(t_env *new, char *value)
{
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (0);
	}
	return (1);
}

void	add_env(t_env **env, char *key, char *value)
=======
void add_env(t_env **env, char *key, char *value)
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
{
	t_env *new;
	t_env *tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return;
	new->key = ft_strdup(key);
	if (new->key)
	{
<<<<<<< HEAD
		if (!set_env_value(new, value))
			return ;
=======
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			return;
		}
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
	}
	else
	{
		new->value = NULL;
<<<<<<< HEAD
=======
	}
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
	new->next = NULL;
	if (*env == NULL)
	{
		*env = new;
	}
	else
	{
		tmp = *env;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	parse_env_string(const char *env_str, char **key, char **value)
{
	int	j;

	j = 0;
	while (env_str[j] != '=' && env_str[j] != '\0')
		j++;
	if (env_str[j] == '\0')
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	*key = malloc((j + 1) * sizeof(char));
	strncpy(*key, env_str, j);
	(*key)[j] = '\0';
	*value = malloc((strlen(env_str) - j) * sizeof(char));
	strcpy(*value, env_str + j + 1);
}

t_env	*get_env(char ***envp, t_env *env)
{
	int		i;
	char	**envp_cpy;
	char	*key;
	char	*value;

	if (envp == NULL || *envp == NULL)
		return (env);
	i = 0;
	envp_cpy = *envp;
	while (envp_cpy[i])
	{
		parse_env_string(envp_cpy[i], &key, &value);
		if (key && value)
		{
			add_env(&env, key, value);
			free(key);
			free(value);
			
		}
		i++;
	}
	return (env);
}
