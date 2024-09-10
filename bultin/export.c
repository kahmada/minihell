/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:29:48 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/10 19:43:55 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_invalid_identifier(char **key, char **value)
{
	fprintf(stderr, "minishell: export: `%s`:not a valid identifier\n", *key);
	free(*key);
	*key = NULL;
	*value = NULL;
}

void	validate_and_parse_export(const char *arg, char **key, char **value, int *append_mode)
{
	*append_mode = 0;
	*key = ft_strdup(arg);
	if ((*key)[0] == '=' || (*key)[0] == '$' || ft_strchr(*key, '=') == *key)
	{
		handle_invalid_identifier(key, value);
		return ;
	}
	*value = ft_strchr(*key, '=');
	if (!*value || *(*value + 1) == '\0')
	{
		free(*key);
		// *key = NULL;
		*value = NULL;
		return ;
	}
	**value = '\0';
	(*value)++;
	if ((*key)[ft_strlen(*key) - 1] == '+')
	{
		*append_mode = 1;
		(*key)[ft_strlen(*key) - 1] = '\0';
	}
	if (!is_valid_variable_name(*key))
		handle_invalid_identifier(key, value);
}

void	handle_export_modes(t_env **env, char *key, char *value, int append_mode)
{
	t_env	*existing;
	char	*new_value;

	if (append_mode)
	{
		existing = find_env(*env, key);
		if (existing)
		{
			new_value = malloc(ft_strlen(existing->value) + ft_strlen(value) + 1);
			if (!new_value)
			{
				perror("malloc");
				return ;
			}
			ft_strcpy(new_value, existing->value);
			ft_strcat(new_value, value);
			free(existing->value);
			existing->value = new_value;
		}
		else
			add_env(env, key, value);
	}
	else
		update_environment(env, key, value, append_mode);
}

void	bult_export(t_command *cmd, t_env **env)
{
	// print_command(cmd);
	// exit(1);
	int		i;
	char	*key;
	char	*value;
	int		append_mode;

	i = 1;
	if (!cmd->args[i])
	{
		print_export(*env);
		return ;
	}
	while (cmd->args[i])
	{
		validate_and_parse_export(cmd->args[i], &key, &value, &append_mode);
		// printf("key is==>>%s\n", key);
		// printf("value is===>>%s\n", value);
		// if (!key || !value)
		// {
		// 	manage_exit_status(1, 1);
		// 	i++;
		// 	continue ;
		// }
		handle_export_modes(env, key, value, append_mode);
		// free(key);
		i++;
	}
	manage_exit_status(0, 1);
}
