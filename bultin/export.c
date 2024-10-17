/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:29:48 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/17 16:48:04 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_value(const char *existing_value, const char *new_value)
{
	char	*result;

	result = malloc(ft_strlen(existing_value) + ft_strlen(new_value) + 1);
	if (!result)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strcpy(result, existing_value);
	ft_strcat(result, new_value);
	return (result);
}

void	handle_export_modes(t_env **env, char *key, char *value, int ap_md)
{
	t_env	*existing;
	char	*new_value;

	existing = find_env(*env, key);
	if (ap_md)
	{
		if (existing)
		{
			new_value = append_value(existing->value, value);
			if (!new_value)
				return ;
			free(existing->value);
			existing->value = new_value;
		}
		else
			add_env(env, key, value);
	}
	else
	{
		if (value && *value != '\0')
			update_environment(env, key, value);
		else if (!existing)
			add_env(env, key, "");
	}
}

void	process_export_argument(t_command *cmd, t_env **env, char *arg)
{
	char	*key;
	char	*value;
	int		append_mode;

	valid_and_prs_exprt(arg, &key, &value, &append_mode);
	if (key == NULL)
	{
		cmd->ex = manage_exit_status(EXIT_FAILURE, 1);
		free(cmd->ex);
		return ;
	}
	handle_export_modes(env, key, value, append_mode);
	free(key);
}

void	bult_export(t_command *cmd, t_env **env)
{
	int		i;

	i = 1;
	if (!cmd->args[i])
	{
		print_export(*env);
		cmd->ex = manage_exit_status(EXIT_SUCCESS, 1);
		free(cmd->ex);
		return ;
	}
	while (cmd->args[i])
	{
		process_export_argument(cmd, env, cmd->args[i]);
		i++;
	}
}
