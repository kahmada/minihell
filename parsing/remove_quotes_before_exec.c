/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_before_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:12 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 17:10:37 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_initialize(t_data *mydata, char *arg)
{
	mydata->j = 0;
	mydata->k = 0;
	mydata->in_quotes = 0;
	mydata->new_arg = (char *)malloc(ft_strlen(arg) + 1);
	if (!(mydata->new_arg))
		return ;
}

static void	remove_quotes(char **args)
{
	t_data	mydata;

	mydata.i = -1;
	while (args[++(mydata.i)])
	{
		ft_initialize(&mydata, args[mydata.i]);
		while (args[mydata.i][mydata.j])
		{
			if (!(mydata.in_quotes) && (args[mydata.i][mydata.j] == '\''
				|| args[mydata.i][mydata.j] == '\"'))
			{
				mydata.in_quotes = 1;
				mydata.quote_char = args[mydata.i][mydata.j];
			}
			else if (mydata.in_quotes
				&& args[mydata.i][mydata.j] == mydata.quote_char)
				mydata.in_quotes = 0;
			else
				(mydata.new_arg)[(mydata.k)++] = args[mydata.i][mydata.j];
			mydata.j++;
		}
		(mydata.new_arg)[mydata.k] = '\0';
		free(args[mydata.i]);
		args[mydata.i] = mydata.new_arg;
	}
}

void	remove_quotes_end(t_command *cmd)
{
	while (cmd)
	{
		remove_quotes(cmd->args);
		cmd = cmd->next;
	}
}
