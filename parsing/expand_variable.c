/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:05:14 by chourri           #+#    #+#             */
/*   Updated: 2024/09/14 11:05:25 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *expand_variable(char *data, char **envp)
{
	size_t exp_len;
	char *exp;
	char *ptr;
	const char *start;
	int var_len;
	char *var;
	char *value;
	int i;
	char	*ex;
	exp_len = expanded_len(data, envp);
	exp = malloc(exp_len + 1);
	if (!exp)
		return NULL;

	ptr = exp;
	while (*data)
	{
		if (*data == '$' && *(data+1) == '?')
		{
			ex = manage_exit_status(0, 0);
			strcpy(ptr, ex);
			ptr += ft_strlen(ex);
			free(ex);
			data += 2;
		}
		else if (*data == '$' && is_alnum(*(data + 1)))
		{
			data++;
			if (*data == '0')
			{
				strcpy(ptr, "bash");
				ptr += 4;
				data++;
			} else if (*data == '-')
			{
				strcpy(ptr, "himBH");
				ptr += 5;
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
				value = "";
				while (envp[i])
				{
					if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
					{
						value = envp[i] + var_len + 1;
						break;
					}
					i++;
				}
				strcpy(ptr, value);
				ptr += strlen(value);
				free(var);
			}
		}
		else
			*ptr++ = *data++;
	}
	*ptr = '\0';
	return exp;
}
