/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_syntax2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:41 by chourri           #+#    #+#             */
/*   Updated: 2024/10/15 18:05:26 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	multiple_pipes_error(void)
{
	parse_error("multiple pipes with no command in between\n");
}

static int	pipe_parsing(t_token *lst)
{
	t_token	*curr;
	t_token	*fin;

	curr = lst;
	fin = last_token(lst);
	if (lst->type == PIPE)
		return (parse_error("near unexpected token `|'\n"), 1);
	else if (fin->type == PIPE)
		return (parse_error("unexpected end of command after '|'\n"), 1);
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (curr->next == NULL || curr->next->type == PIPE)
				return (multiple_pipes_error(), 1);
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (curr == NULL || !redirection_symbols(curr->type))
				return (multiple_pipes_error(), 1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	heredoc_parsing(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (handle_heredoc(curr, lst))
			curr = curr->next;
		if (curr->type == HEREDOC)
		{
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (lst->sig_flag == 1)
				return (1);
			if (!curr)
				return (parse_error("near unexpected token `newline'\n"), 1);
			else if (curr->type != WORD && curr->type != INSIDE_DOUBLE_QUOTE
				&& curr->type != INSIDE_SINGLE_QUOTE && curr->type != DS)
				return (parse_error("near unexpected token `<<'\n"), 1);
			else if (curr && curr->type == HEREDOC)
				return (parse_error("near unexpected token `<<'\n"), 1);
		}
		curr = curr->next;
	}
	return (0);
}

int	parsing(t_token *lst)
{
	char	*ex;

	if ((pipe_parsing(lst) || heredoc_parsing(lst)
			|| redirect_append(lst) || redirect_in_parsing(lst)
			|| redirect_out_parsing(lst)))
	{
		if (lst->sig_flag == 0)
		{
			ex = manage_exit_status(258, 1);
			free(ex);
		}
		return (1);
	}
	return (0);
}
