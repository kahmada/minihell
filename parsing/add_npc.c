/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_npc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:04 by chourri           #+#    #+#             */
/*   Updated: 2024/09/07 12:18:57 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//$pwd$?yser
int is_alphabet(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void len_to_add(char c1, char c2, int *extra_len, int *i)
{
	if ((c1 == '$' && c2 == '?') || (c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<'))
	{
		(*extra_len) += 2;
		(*i)++;
	}
	else if (c1 == '"' || c1 == '\'' || c1 == '$' || c1 == '*' || c1 == '!')
		(*extra_len)++;
	else if (c1 == ' ' || c1 == '\t')
		(*extra_len) += 2;
	else if (c1 == '<' || c1 == '>' || c1 == '|')
		(*extra_len) += 2;
}

int calculate_len(char *input)
{
	int i;
	int extra_len;

	extra_len = 0;
	i = 0;
	while (input[i])
	{
		len_to_add(input[i], input[i + 1], &extra_len, &i);
		if (input[i] == '$' && is_alphabet(input[i + 1]))
		{
			int j = i + 1;
			while (input[j] && is_alphabet(input[j]))
				j++;
			if (input[j] == '$' || input[j] == '?')
				extra_len++;
		}
		i++;
	}
	return (extra_len);
}

void handle_quotes(char *input, char **new, int *i)
{
	char quote;

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

void handle_dollar_sign(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
}
void handle_heredoc_append(char *input, char **new, int *i)
{
		*(*new)++ = NON_PRINTABLE_CHAR;
		*(*new)++ = input[(*i)++];
		*(*new)++ = input[(*i)];
		*(*new)++ = NON_PRINTABLE_CHAR;
}

void handle_pipe_in_out_redirections(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
	*(*new)++ = NON_PRINTABLE_CHAR;
}
void handle_exit_status(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[(*i)++];
	*(*new)++ = input[*i];
	*(*new)++ = NON_PRINTABLE_CHAR;
}

void handle_space_tab(char *input, char **new, int *i)
{
		*(*new)++ = NON_PRINTABLE_CHAR;
		*(*new)++ = input[*i];
		*(*new)++ = NON_PRINTABLE_CHAR; //
}
void handle_star(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
}
void create_new_string(char *input, char **new_input)
{
	int i;
	char *new;

	i = -1;
	new = *new_input;
	while (input[++i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
			handle_exit_status(input, &new, &i);
		else if (input[i] == '$' && (i == 0 || input[i - 1] != ' '))
			handle_dollar_sign(input, &new, &i);
		else if ((input[i] == '"' || input[i] == '\''))
			handle_quotes(input, &new, &i);
		else if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
				handle_heredoc_append(input, &new, &i);
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			handle_pipe_in_out_redirections(input, &new, &i);
		else if (input[i] == ' ' || input[i] == '\t')
				handle_space_tab(input, &new, &i);
		else if (i > 0 && (input[i] == '*' || input[i] == '!') && input[i - 1] != '$')
			handle_star(input, &new, &i);
		else
			*new ++ = input[i];
	}
	*new = '\0';
}

void add_npc_to_cmd(char *input, char **new_input)
{
	int len_to_add;

	len_to_add = calculate_len(input);
	*new_input = malloc(len_to_add + strlen(input) + 1);
	if (!new_input)
		return;
	create_new_string(input, new_input);
}

