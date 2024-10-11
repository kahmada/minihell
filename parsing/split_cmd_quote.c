/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:45 by chourri           #+#    #+#             */
/*   Updated: 2024/10/11 10:49:38 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	len_word(char const *s)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && quote == 0)
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		else if ((s[i] == ' ' || s[i] == '\t') && quote == 0)
			break ;
		i++;
	}
	return (i);
}

static char	*allocate_copy_word(char const *s, size_t len)
{
	char	*word;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, s, len);
	word[len] = '\0';
	return (word);
}

static int	num_words(char const *s)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && ((s[i] != ' ' && s[i] != '\t') || quote))
			{
				if ((s[i] == '\'' || s[i] == '\"') && quote == 0)
					quote = s[i];
				else if (s[i] == quote)
					quote = 0;
				i++;
			}
		}
	}
	return (count);
}

char	**ft_split_cmd_quote(char const *s)
{
	t_var	var;

	var.i = 0;
	if (!s)
		return (NULL);
	var.num = num_words(s);
	var.array = (char **)malloc(sizeof(char *) * (var.num + 1));
	if (!(var.array))
		return (NULL);
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
		{
			var.len = len_word(s);
			var.array[var.i] = allocate_copy_word(s, var.len);
			if (!var.array[var.i])
				return (free_word_array(var.array), NULL);
			var.i++;
			s += var.len;
		}
	}
	var.array[var.i] = NULL;
	return (var.array);
}
