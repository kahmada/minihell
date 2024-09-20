/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:25:04 by chourri           #+#    #+#             */
/*   Updated: 2024/09/19 14:07:41 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_data(char *combined_data, char *data, int flag)
{
	char	*temp;

	if (combined_data)
	{
		if (flag)
			temp = ft_strjoin_space(combined_data, data);
		else
			temp = ft_strjoin(combined_data, data);
		free(combined_data);
	}
	else
		temp = ft_strdup(data);
	return (temp);
}

static void	ft_join(char **combined_data, char *data)
{
	(*combined_data) = join_data((*combined_data), " ", 1);
	(*combined_data) = join_data((*combined_data), data, 1);
	(*combined_data) = join_data((*combined_data), " ", 1);
}

static void	ft_initialize(t_data *mydata)
{
	mydata->new = NULL;
	mydata->combined = NULL;
}

t_token	*build_new_tokens_pipe(t_token *token)
{
	t_data	mydt;

	ft_initialize(&mydt);
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (is_redirection_symbol(token->type))
				ft_join(&(mydt.combined), token->data);
			else
				(mydt.combined) = join_data((mydt.combined), token->data, 0);
			if (!(mydt.combined))
				return (free_list(mydt.new));
			token = token->next;
		}
		if ((mydt.combined))
		{
			ft_lstadd_back_new(&(mydt.new), WORD, (mydt.combined));
			free((mydt.combined));
			(mydt.combined) = NULL;
		}
		if (token)
			token = token->next;
	}
	return (mydt.new);
}

t_command	*build_cmd(t_token *new_token)
{
	t_data	mydata;

	mydata.cmd = NULL;
	mydata.head = NULL;
	mydata.prev = NULL;
	while (new_token)
	{
		mydata.cmd = (t_command *)malloc(sizeof(t_command));
		if (!(mydata.cmd))
			return (NULL);
		if (ft_strchr(new_token->data, '"') || ft_strchr(new_token->data, '\''))
			(mydata.cmd)->args = ft_split_cmd_quote(new_token->data);
		else
			(mydata.cmd)->args = ft_split_cmd(new_token->data);
		if (!(mydata.cmd)->args)
			return (NULL);
		(mydata.cmd)->next = NULL;
		if (!(mydata.head))
			(mydata.head) = (mydata.cmd);
		if (mydata.prev)
			(mydata.prev)->next = mydata.cmd;
		mydata.prev = mydata.cmd;
		new_token = new_token->next;
	}
	return (mydata.head);
}
