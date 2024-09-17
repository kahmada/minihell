/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:05:14 by chourri           #+#    #+#             */
/*   Updated: 2024/09/17 12:45:34 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(char **data, char **ptr)
{
	char	*exit_status;

	exit_status = manage_exit_status(0, 0);
	ft_strcpy(*ptr, exit_status);
	*ptr += ft_strlen(exit_status);
	free(exit_status);
	*data += 2;
}

void	expand_env_variable(char **data, char **ptr, char **envp)
{
	t_data	mydata;

	mydata.start = *data;
	while (**data && **data != ' ' && **data != '$' && is_alnum(**data))
		(*data)++;
	mydata.var_len = *data - mydata.start;
	mydata.var = ft_strndup(mydata.start, mydata.var_len);
	mydata.i = 0;
	mydata.value = "";
	while (envp[mydata.i])
	{
		if (ft_strncmp(envp[mydata.i], mydata.var, mydata.var_len) == 0
			&& envp[mydata.i][mydata.var_len] == '=')
		{
			mydata.value = envp[mydata.i] + mydata.var_len + 1;
			break ;
		}
		mydata.i++;
	}
	ft_strcpy(*ptr, mydata.value);
	*ptr += strlen(mydata.value);
	free(mydata.var);
}

void	expand_variable_value(char **data, char **ptr, char **envp)
{
	if (**data == '0')
	{
		ft_strcpy(*ptr, "bash");
		*ptr += 4;
		(*data)++;
	}
	else if (**data == '-')
	{
		ft_strcpy(*ptr, "himBH");
		*ptr += 5;
		(*data)++;
	}
	else if (is_digit(**data))
		(*data)++;
	else
	{
		expand_env_variable(data, ptr, envp);
	}
}

char	*expand_variable(char *data, char **envp)
{
	t_data	mydata;

	mydata.exp_len = expanded_len(data, envp);
	mydata.exp = malloc(mydata.exp_len + 1);
	if (!mydata.exp)
		return (NULL);
	mydata.ptr = mydata.exp;
	while (*data)
	{
		if (*data == '$' && *(data + 1) == '?')
			exit_status(&data, &mydata.ptr);
		else if (*data == '$' && is_alnum(*(data + 1)))
		{
			data++;
			expand_variable_value(&data, &mydata.ptr, envp);
		}
		else
			*mydata.ptr++ = *data++;
	}
	*mydata.ptr = '\0';
	return (mydata.exp);
}
