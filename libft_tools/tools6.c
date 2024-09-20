/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:47:57 by chourri           #+#    #+#             */
/*   Updated: 2024/09/19 19:37:56 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_' || c == '-');
}

int	is_digit(char c)
{
	return (c >= '1' && c <= '9');
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*dup;

	dup = malloc(n + 1);
	i = 0;
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	check_heredoc_presence(t_token *token)
{
	int	is_heredoc;

	is_heredoc = 0;
	if (token)
	{
		token = token->previous;
		while (token && token->type != HEREDOC)
		{
			token = token->previous;
		}
		if (token && token->type == HEREDOC)
			is_heredoc = 1;
		else
			is_heredoc = 0;
	}
	return (is_heredoc);
}
