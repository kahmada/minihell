/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:29:48 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/13 14:57:58 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_export_modes(t_env **env, char *key, char *value, int ap_md)
{
	t_env	*existing;
	char	*new_value;

	if (ap_md)
	{
		existing = find_env(*env, key);
		if (existing)
		{
			new_value = malloc(ft_strlen(existing->value)
					+ ft_strlen(value) + 1);
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
		update_environment(env, key, value);
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
