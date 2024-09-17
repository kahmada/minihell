/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:05:14 by chourri           #+#    #+#             */
/*   Updated: 2024/09/15 13:48:13 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(t_data *mydata, char **data)
{
	mydata->ex = manage_exit_status(0, 0);
	ft_strcpy(mydata->ptr, mydata->ex);
	mydata->ptr += ft_strlen(mydata->ex);
	free(mydata->ex);
	*data += 2;
}

void	numeric_var(t_data *mydata, char **data)
{
	if (**data == '0')
	{
		ft_strcpy(mydata->ptr, "bash");
		mydata->ptr += 4;
		(*data)++;
	}
	else if (**data == '-')
	{
		ft_strcpy(mydata->ptr, "himBH");
		mydata->ptr += 5;
		(*data)++;
	}
	else if (is_digit(**data))
		(*data)++;
}

void	expand_env_var(t_data *mydata, char **data, char **envp)
{
	mydata->start = *data;
	while (**data && **data != ' ' && **data != '$' && is_alnum(**data))
		(*data)++;
	mydata->var_len = *data - mydata->start;
	mydata->var = ft_strndup(mydata->start, mydata->var_len);
	mydata->i = 0;
	mydata->value = "";
	while (envp[mydata->i])
	{
		if (ft_strncmp(envp[mydata->i], mydata->var, mydata->var_len) == 0
			&& envp[mydata->i][mydata->var_len] == '=')
		{
			mydata->value = envp[mydata->i] + mydata->var_len + 1;
			break ;
		}
		(mydata->i)++;
	}
	ft_strcpy(mydata->ptr, mydata->value);
	mydata->ptr += strlen(mydata->value);
	free(mydata->var);
}

void	normal_char(t_data *mydata, char **data)
{
	*(mydata->ptr)++ = *(*data)++;
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
			exit_status(&mydata, &data);
		else if (*data == '$' && is_alnum(*(data + 1)))
		{
			data++;
			if (*data == '0' || *data == '-')
				numeric_var(&mydata, &data);
			else
				expand_env_var(&mydata, &data, envp);
		}
		else
			normal_char(&mydata, &data);
	}
	*(mydata.ptr) = '\0';
	return (mydata.exp);
}
