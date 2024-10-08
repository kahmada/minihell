/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:06:08 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/08 17:14:43 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	if (!src || !dst)
		return (0);
	src_len = ft_strlen(src);
	if (src_len + 1 < dstsize)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len);
}

static void	free_sp(char **str, size_t count)
{
	size_t	i;

	i = 0;
	while (str[i] && i < count)
		free(str[i++]);
	free(str);
}

static	int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
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

static	char	**fill_sp(char **res, char const *s, char c)
{
	int	i;
	int	temp;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			temp = i;
			while (s[i] != c && s[i])
				i++;
			res[j] = malloc(i - temp + 1);
			if (!res[j])
				return (NULL);
			ft_strlcpy(res[j++], s + temp, i - temp + 1);
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split_lib(char const *s, char c)
{
	char	**result;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_sp(result, s, c))
	{
		free_sp(result, count);
		return (NULL);
	}
	return (result);
}
