/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_before_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:12 by chourri           #+#    #+#             */
/*   Updated: 2024/10/11 10:08:25 by chourri          ###   ########.fr       */
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

static void	update_args(char **args, t_data *mydata)
{
	(mydata->new_arg)[mydata->k] = '\0';
	free(args[mydata->i]);
	args[mydata->i] = mydata->new_arg;
}

static void	remove_quotes(char **args)
{
	t_data	dt;

	dt.i = -1;
	while (args[++(dt.i)])
	{
		if (ft_strlen(args[dt.i]) == 1 && (args[dt.i][0] == '"'
			|| args[dt.i][0] == '\''))
			return ;
		ft_initialize(&dt, args[dt.i]);
		while (args[dt.i][dt.j])
		{
			if (!(dt.in_quotes) && (args[dt.i][dt.j] == '\''
				|| args[dt.i][dt.j] == '\"'))
			{
				dt.in_quotes = 1;
				dt.quote_char = args[dt.i][dt.j];
			}
			else if (dt.in_quotes && args[dt.i][dt.j] == dt.quote_char)
				dt.in_quotes = 0;
			else
				(dt.new_arg)[(dt.k)++] = args[dt.i][dt.j];
			dt.j++;
		}
		update_args(args, &dt);
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
