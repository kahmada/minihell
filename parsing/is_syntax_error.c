/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:08:40 by chourri           #+#    #+#             */
/*   Updated: 2024/10/15 21:29:57 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirect_in_parsing_bool(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->type == REDIRECT_IN)
		{
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (lst->sig_flag == 1)
				return (1);
			if (!curr)
				return (1);
			else if (curr->type != WORD && curr->type != INSIDE_DOUBLE_QUOTE
				&& curr->type != INSIDE_SINGLE_QUOTE && curr->type != DS)
				return (1);
			else if (curr && curr->type == REDIRECT_IN)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	redirect_out_parsing_bool(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->type == REDIRECT_OUT)
		{
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (lst->sig_flag == 1)
				return (1);
			if (!curr)
				return (1);
			else if (curr->type != WORD && curr->type != INSIDE_DOUBLE_QUOTE
				&& curr->type != INSIDE_SINGLE_QUOTE)
				return (1);
			else if (curr && curr->type == REDIRECT_OUT)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	redirect_append_bool(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->type == REDIRECT_APPEND)
		{
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (lst->sig_flag == 1)
				return (1);
			if (!curr)
				return (1);
			else if (curr->type != WORD && curr->type != INSIDE_DOUBLE_QUOTE
				&& curr->type != INSIDE_SINGLE_QUOTE)
				return (1);
			else if (curr && curr->type == REDIRECT_APPEND)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	heredoc_parsing_bool(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			curr = curr->next;
			while (curr && (curr->type == TAAB || curr->type == SPAACE))
				curr = curr->next;
			if (lst->sig_flag == 1)
				return (1);
			if (!curr)
				return (1);
			else if (curr->type != WORD && curr->type != INSIDE_DOUBLE_QUOTE
				&& curr->type != INSIDE_SINGLE_QUOTE && curr->type != DS)
				return (1);
			else if (curr && curr->type == HEREDOC)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	should_open_heredoc(t_token *lst)
{
	if (redirect_append_bool(lst)
		|| redirect_in_parsing_bool(lst)
		|| redirect_out_parsing_bool(lst)
		|| heredoc_parsing_bool(lst))
		return (1);
	return (0);
}
