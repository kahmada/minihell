/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:29:48 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/13 17:49:35 by kahmada          ###   ########.fr       */
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
		// free(*key);
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
	{
		// printf("enter here2");
		update_environment(env, key, value, append_mode);
	}
}

void	bult_export(t_command *cmd, t_env **env)
{

	int		i;
	char	*key;
	char	*value;
	int		append_mode;
	char *ex;

	i = 1;
	if (!cmd->args[i])
	{
		print_export(*env);
		ex=manage_exit_status(EXIT_SUCCESS, 1);
		free(ex);
		return ;
	}
	while (cmd->args[i])
	{
		validate_and_parse_export(cmd->args[i], &key, &value, &append_mode);
		if (key == NULL)
		{
			ex=manage_exit_status(EXIT_FAILURE, 1); // Set failure status on invalid export
			free(ex);
			i++;
			continue; // Skip to the next argument
		}
		handle_export_modes(env, key, value, append_mode);
		free(key);
		i++;
	}
	ex=manage_exit_status(EXIT_SUCCESS, 1); 
	free(ex);
}
