/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:32:55 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/03 10:39:34 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_quotes(char **str)
{
	char	*src;
	char	*dst;
	char	*dst_start;

	src = *str;
	dst = (char *)malloc(ft_strlen(src) + 1);
	if (dst == NULL)
	{
		perror("malloc");
		return ;
	}
	dst_start = dst;
	while (*src != '\0')
	{
		if (*src != '\'' && *src != '\"')
		{
			*dst++ = *src;
		}
		src++;
	}
	*dst = '\0';
	free(*str);
	*str = dst_start;
}
