/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_npc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:04 by chourri           #+#    #+#             */
/*   Updated: 2024/09/19 14:06:27 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	len_to_add(char c1, char c2, int *extra_len, int *i)
{
	if ((c1 == '$' && c2 == '?') || (c1 == '>' && c2 == '>')
		|| (c1 == '<' && c2 == '<'))
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

int	calculate_len(char *input)
{
	int	i;
	int	extra_len;
	int	j;

	extra_len = 0;
	i = 0;
	while (input[i])
	{
		len_to_add(input[i], input[i + 1], &extra_len, &i);
		if (input[i] == '$' && input[i + 1] == '$')
		{
			extra_len += 2;
			i++;
		}
		else if (input[i] == '$' && is_alphabet(input[i + 1]))
		{
			j = i + 1;
			while (input[j] && is_alphabet(input[j]))
				j++;
			if (input[j] == '$' || input[j] == '?')
				extra_len++;
		}
		i++;
	}
	return (extra_len);
}

void	handle_space_tab(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
	*(*new)++ = NON_PRINTABLE_CHAR;
}

void	handle_star(char *input, char **new, int *i)
{
	*(*new)++ = NON_PRINTABLE_CHAR;
	*(*new)++ = input[*i];
}
