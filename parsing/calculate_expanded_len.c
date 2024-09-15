/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_expanded_len.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:52:34 by chourri           #+#    #+#             */
/*   Updated: 2024/09/14 11:11:18 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


size_t expanded_len(char *data, char **envp)
{
	size_t	exp_len = 0;
	char	*start;
	int		var_len;
	char	*var;
	int		i;
	char	*ex;

	while (*data)
	{
		if (*data == '$' && *(data + 1) == '?')
		{
			ex = manage_exit_status(0, 0);
			exp_len += ft_strlen(ex);
			free(ex);
			data += 2;
		}
		else if (*data == '$' && is_alnum(*(data + 1)))
		{
			data++;
			if (*data == '0' || *data == '-')
			{
				if (*data == '0')
					exp_len += 4; // "bash"
				else if (*data == '-')
					exp_len += 5; // "himBH"
				data++;
			}
			else if (is_digit(*data))
				data++;
			else
			{
				start = data;
				while (*data && *data != ' ' && *data != '$' && is_alnum(*data))
					data++;
				var_len = data - start;
				var = ft_strndup(start, var_len);
				i = 0;
				while (envp[i])
				{
					if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
					{
						exp_len += ft_strlen(envp[i] + var_len + 1);
						break;
					}
					i++;
				}
				free(var);
			}
		}
		else
		{
			exp_len++;
			data++;
		}
	}
	return exp_len;
}
