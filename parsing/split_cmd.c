/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:05:01 by chourri           #+#    #+#             */
/*   Updated: 2024/10/11 10:49:45 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	len_word(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	return (i);
}

static char	*allocate_copy_word(char const *s)
{
	size_t	len;
	char	*word;

	len = len_word(s);
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

void	free_word_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	num_words(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
		}
	}
	return (count);
}

char	**ft_split_cmd(char const *s)
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
			var.array[var.i] = allocate_copy_word(s);
			if (!var.array[var.i])
				return (free_word_array(var.array), NULL);
			var.i++;
		}
		s += len_word(s);
	}
	var.array[var.i] = NULL;
	return (var.array);
}
