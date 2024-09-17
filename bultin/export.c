/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:29:48 by kahmada           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/15 19:27:07 by kahmada          ###   ########.fr       */
=======
/*   Updated: 2024/09/13 17:49:35 by kahmada          ###   ########.fr       */
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
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

void	valid_and_prs_exprt(const char *arg, char **ky, char **val, int *ap_md)
{
	*ap_md = 0;
	*ky = ft_strdup(arg);
	if ((*ky)[0] == '=' || (*ky)[0] == '$' || ft_strchr(*ky, '=') == *ky)
	{
		handle_invalid_identifier(ky, val);
		return ;
	}
	*val = ft_strchr(*ky, '=');
	if (!*val || *(*val + 1) == '\0')
	{
<<<<<<< HEAD
		*val = NULL;
=======
		// free(*key);
		*value = NULL;
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
		return ;
	}
	**val = '\0';
	(*val)++;
	if ((*ky)[ft_strlen(*ky) - 1] == '+')
	{
		*ap_md = 1;
		(*ky)[ft_strlen(*ky) - 1] = '\0';
	}
	if (!is_valid_variable_name(*ky))
		handle_invalid_identifier(ky, val);
}

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
<<<<<<< HEAD
		update_environment(env, key, value, ap_md);
=======
	{
		// printf("enter here2");
		update_environment(env, key, value, append_mode);
	}
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
}

void	process_export_argument(t_command *cmd, t_env **env, char *arg)
{
<<<<<<< HEAD
=======

	int		i;
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
	char	*key;
	char	*value;
	int		append_mode;
	char *ex;

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
<<<<<<< HEAD
		cmd->ex = manage_exit_status(EXIT_SUCCESS, 1);
		free(cmd->ex);
=======
		ex=manage_exit_status(EXIT_SUCCESS, 1);
		free(ex);
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
		return ;
	}
	while (cmd->args[i])
	{
<<<<<<< HEAD
		process_export_argument(cmd, env, cmd->args[i]);
		i++;
	}
	cmd->ex = manage_exit_status(EXIT_SUCCESS, 1);
	free(cmd->ex);
=======
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
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
}
