/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_npc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:40:22 by chourri           #+#    #+#             */
/*   Updated: 2024/09/12 12:57:31 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(char *input, char **new, int *i)
{
	char	quote;

	quote = input[*i];
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = quote;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		*(*new)++ = input[*i];
		(*i)++;
	}
	if (input[*i] == quote)
	{
		*(*new)++ = quote;
		*(*new)++ = NON_PRINTABLE_CHAR;
	}
}

void	handle_dollar_sign(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
}

void	handle_heredoc_append(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[(*i)++];
	*(*new)++ = input[(*i)];
	*(*new)++ = NON_PRINTABLE_CHAR;
}

void	handle_pipe_in_out_redirections(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
	*(*new)++ = NON_PRINTABLE_CHAR;
}

void	handle_exit_status(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[(*i)++];
	*(*new)++ = input[*i];
	*(*new)++ = NON_PRINTABLE_CHAR;
}
