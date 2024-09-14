/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:51:25 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/14 10:19:48 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atoi(char *s)
{
	long	result;
	int		signe;
	int		i;

	i = 0;
	result = 0;
	signe = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if ((*s) == '-' || (*s) == '+')
	{
		signe = 1 - 2 * (*s++ == '-');
		i++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (*s != '0' && *(s + 1) != '0')
			i++;
		if (i > 11)
			return (LONG_MAX);
		result = result * 10 + (*s++ - '0');
	}
	return (signe * result);
}

int is_alphabet(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	redirection_symbols(int type_symbol)
{
	return ((type_symbol == WORD || type_symbol == HEREDOC || type_symbol == REDIRECT_APPEND || type_symbol == REDIRECT_IN || type_symbol == REDIRECT_OUT || type_symbol == INSIDE_DOUBLE_QUOTE || type_symbol == INSIDE_SINGLE_QUOTE));
}
int	ft_linked_list_search_redirect_symbols(t_token *lst)
{
	t_token *current = lst;
	while (current)
	{
		if (current->type == REDIRECT_APPEND || current->type == REDIRECT_IN || current->type == REDIRECT_OUT)
			return (1);
		current = current->next;
	}
	return (0);
}
void	parse_error(char *msg)
{
	printf("syntax error : %s", msg);
	return ;
}
