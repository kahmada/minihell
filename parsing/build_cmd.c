/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:25:04 by chourri           #+#    #+#             */
/*   Updated: 2024/09/17 11:46:37 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_token_data(char *combined_data, char *data, int flag)
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

void	ft_join(char **combined_data, char *data)
{
	(*combined_data) = join_token_data((*combined_data), " ", 1);
	(*combined_data) = join_token_data((*combined_data), data, 1);
	(*combined_data) = join_token_data((*combined_data), " ", 1);
}

t_token	*build_new_tokens_pipe(t_token *token)
{
	t_token	*new;
	char	*combined_data;

	new = NULL;
	combined_data = NULL;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (is_redirection_symbol(token->type))
				ft_join(&combined_data, token->data);
			else
				combined_data = join_token_data(combined_data, token->data, 0);
			if (!combined_data)
				return (free_list(new));
			token = token->next;
		}
		if (combined_data)
		{
			ft_lstadd_back_new(&new, WORD, combined_data);
			free(combined_data);
			combined_data = NULL;
		}
		if (token)
			token = token->next;
	}
	return (new);
}

t_command	*build_cmd(t_token *new_token)
{
	t_command	*cmd;
	t_command	*head;
	t_command	*prev;

	cmd = NULL;
	head = NULL;
	prev = NULL;
	while (new_token)
	{
		cmd = (t_command *)malloc(sizeof(t_command));
		if (!cmd)
			return (NULL);
		if (ft_strchr(new_token->data, '"') || ft_strchr(new_token->data, '\''))
			cmd->args = ft_split_cmd_quote(new_token->data);
		else
			cmd->args = ft_split_cmd(new_token->data);
		if (!cmd->args)
			return (NULL);
		cmd->next = NULL;
		if (!head)
			head = cmd;
		if (prev)
			prev->next = cmd;
		prev = cmd;
		new_token = new_token->next;
	}
	return (head);
}
