/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_expanded_len.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:52:34 by chourri           #+#    #+#             */
/*   Updated: 2024/10/17 13:56:20 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_exit_status(char **data)
{
	char	*exit_status;
	size_t	len;

	exit_status = manage_exit_status(0, 0);
	len = ft_strlen(exit_status);
	free(exit_status);
	*data += 2;
	return (len);
}

static size_t	handle_numeric_var(char **data)
{
	size_t	len;

	len = 0;
	if (**data == '0')
		len = 4;
	else if (**data == '-')
		len = 5;
	(*data)++;
	return (len);
}

static size_t	expand_var(char **data, char **envp)
{
	t_data	mydata;

	if (!envp || !*envp)
		return (0);
	mydata.start = *data;
	while (**data && **data != ' ' && **data != '$' && is_alnum(**data))
		(*data)++;
	mydata.var_len = *data - mydata.start;
	mydata.var = ft_strndup(mydata.start, mydata.var_len);
	mydata.i = 0;
	while (envp[mydata.i])
	{
		if (ft_strncmp(envp[mydata.i], mydata.var, mydata.var_len) == 0
			&& envp[mydata.i][mydata.var_len] == '=')
		{
			free(mydata.var);
			return (ft_strlen(envp[mydata.i] + mydata.var_len + 1));
		}
		mydata.i++;
	}
	free(mydata.var);
	return (0);
}

static void	handle_normal_char(char **data, size_t *exp_len)
{
	(*exp_len)++;
	(*data)++;
}

size_t	expanded_len(char *data, char **envp)
{
	t_data	mydata;

	mydata.exp_len = 0;
	while (*data)
	{
		if (*data == '$' && *(data + 1) == '?')
			mydata.exp_len += ft_exit_status(&data);
		else if (*data == '$' && is_alnum(*(data + 1)))
		{
			data++;
			if (*data == '0' || *data == '-')
				mydata.exp_len += handle_numeric_var(&data);
			else if (is_digit(*data))
				data++;
			else
				mydata.exp_len += expand_var(&data, envp);
		}
		else
			handle_normal_char(&data, &mydata.exp_len);
	}
	return (mydata.exp_len);
}
