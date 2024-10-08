/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_npc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:47:17 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 20:37:36 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_pid(char *input, char **new, int	*i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[(*i)++];
	*(*new)++ = input[(*i)];
	*(*new)++ = NON_PRINTABLE_CHAR;
}

static int	process_special_chars(char *input, char **new_input, int *i)
{
	char	*new;

	new = *new_input;
	if (input[*i] == '$' && input[*i + 1] == '?')
		handle_exit_status(input, &new, i);
	else if (input[*i] == '$' && input[*i + 1] == '$')
		handle_pid(input, &new, i);
	else if (input[*i] == '$' && (*i == 0 || input[*i - 1] != ' '))
		handle_dollar_sign(input, &new, i);
	else if (input[*i] == '"' || input[*i] == '\'')
		handle_quotes(input, &new, i);
	else if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
		handle_heredoc_append(input, &new, i);
	else if (input[*i] == '>' || input[*i] == '<' || input[*i] == '|')
		handle_pipe_in_out_redirections(input, &new, i);
	else if (input[*i] == ' ' || input[*i] == '\t')
		handle_space_tab(input, &new, i);
	else if (*i > 0 && (input[*i] == '*' || input[*i] == '!')
		&& input[*i - 1] != '$')
		handle_star(input, &new, i);
	else
		return (0);
	*new_input = new;
	return (1);
}

static void	handle_input_chars(char *input, char **new_input, int *i)
{
	char	*new;

	new = *new_input;
	if (!new)
		return ;
	if (!process_special_chars(input, &new, i))
		*new++ = input[*i];
	*new_input = new;
}

static void	create_new_string(char *input, char **new_input)
{
	int		i;
	char	*new;

	new = *new_input;
	if (!new)
		return ;
	i = -1;
	while (input[++i])
		handle_input_chars(input, &new, &i);
	*new = '\0';
}

void	add_npc_to_cmd(char *input, char **new_input)
{
	int	len_to_add;

	len_to_add = calculate_len(input);
	*new_input = malloc(len_to_add + ft_strlen(input) + 1);
	if (!new_input)
		return ;
	create_new_string(input, new_input);
}
