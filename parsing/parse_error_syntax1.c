/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_syntax1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:01:10 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 19:43:57 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc(t_token *current, t_token *lst)
{
	const char	*limiter;

	if (should_open_heredoc(lst) && current->type == HEREDOC && lst->flag == 0
		&& ft_linked_list_search_redirect_symbols(lst))
	{
		current = current->next;
		while (current && current->data
			&& (current->type == SPAACE || current->type == TAAB))
			current = current->next;
		if (current && (current->type == WORD
				|| current->type == INSIDE_DOUBLE_QUOTE
				|| current->type == INSIDE_SINGLE_QUOTE))
		{
			limiter = current->data;
			handle_child_error(limiter, lst);
			lst->flag = 1;
			return (1);
		}
	}
	return (0);
}

int	redirect_in_parsing(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (handle_heredoc(curr, lst))
			curr = curr->next;
		if (curr->type == REDIRECT_IN)
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
				return (parse_error("near unexpected token `<'\n"), 1);
			else if (curr && curr->type == REDIRECT_IN)
				return (parse_error("near unexpected token `<'\n"), 1);
		}
		curr = curr->next;
	}
	return (0);
}

int	redirect_out_parsing(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (handle_heredoc(curr, lst))
			curr = curr->next;
		if (curr->type == REDIRECT_OUT)
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
				return (parse_error("near unexpected token `>'\n"), 1);
			else if (curr && curr->type == REDIRECT_OUT)
				return (parse_error("near unexpected token `>'\n"), 1);
		}
		curr = curr->next;
	}
	return (0);
}

int	redirect_append(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (handle_heredoc(curr, lst))
			curr = curr->next;
		if (curr->type == REDIRECT_APPEND)
		{
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (lst->sig_flag == 1)
				return (1);
			if (!curr)
				return (parse_error("near unexpected token newline'\n"), 1);
			else if (curr->type != WORD && curr->type != INSIDE_DOUBLE_QUOTE
				&& curr->type != INSIDE_SINGLE_QUOTE && curr->type != DS)
				return (parse_error("near unexpected token >>'\n"), 1);
			else if (curr && curr->type == REDIRECT_APPEND)
				return (parse_error("near unexpected token >>'\n"), 1);
		}
		curr = curr->next;
	}
	return (0);
}

int	parse_quotes(char *s)
{
	int	is_quotes;

	is_quotes = 0;
	while (*s)
	{
		if (is_quotes == 0 && *s == '\'')
			is_quotes = 1;
		else if (is_quotes == 0 && *s == '\"')
			is_quotes = -1;
		else if (is_quotes == 1 && *s == '\'')
			is_quotes = 0;
		else if (is_quotes == -1 && *s == '\"')
			is_quotes = 0;
		s++;
	}
	if (is_quotes)
		return (parse_error("quote not closed\n"), is_quotes);
	return (is_quotes);
}
