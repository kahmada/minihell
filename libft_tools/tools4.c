/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:46:23 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/06 19:52:25 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	if (dst == NULL && src == NULL)
		return (dst);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (const unsigned char *)src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src++);
		n--;
	}
	return (dst);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && len == 0 && !needle)
		return (NULL);
	if (!*needle)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *) haystack + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if(!s)
		return 0;
	while (s[i] != '\0')
	{
		// printf("i = %zu\n", i);
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*cpy;
	size_t	i;

	len = ft_strlen(s1);
	cpy = (char *)malloc((len + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	if (cpy != NULL)
	{
		i = 0;
		while (i < len)
		{
			cpy[i] = s1[i];
			i++;
		}
		cpy[i] = '\0';
	}
	return (cpy);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
	{
		// printf("jj\n");
		return ((char *)s2);
	}
	if (!s2 && s1)
		return (ft_strdup(s1));
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++ ;
	}
	j = 0;
	while (s2[j])
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	// if (s1)
	// 	free((char *)s1);
	return (new_s);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
	{
		// printf("jj\n");
		return ((char *)s2);
	}
	if (!s2 && s1)
		return ((char *)s1);
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++ ;
	}
	j = 0;
	while (s2[j])
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	// if (s1)
	// free((char *)s2);
	// free((char *)s1);
	return (new_s);
}
