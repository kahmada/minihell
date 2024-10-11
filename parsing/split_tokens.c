/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:18:22 by chourri           #+#    #+#             */
/*   Updated: 2024/10/11 10:49:50 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	len_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*allocate_copy_word(char const *s, char c)
{
	size_t	len;
	char	*word;

	len = len_word(s, c);
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	if (word)
		ft_strlcpy(word, s, len + 1);
	return (word);
}

static int	num_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	**ft_split_tokens(char const *s, char c)
{
	t_var	var;

	var.i = 0;
	if (!s)
		return (NULL);
	var.num = num_words(s, c);
	var.array = (char **)malloc(sizeof(char *) * (var.num + 1));
	if (!(var.array))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			var.array[var.i] = allocate_copy_word(s, c);
		if (!var.array[var.i])
			return (free_word_array(var.array), NULL);
		if (*s)
			var.i++;
		s += len_word(s, c);
		while (*s && *s == c)
			s++;
	}
	var.array[var.i] = NULL;
	return (var.array);
}
