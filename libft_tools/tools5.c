/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:51:25 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/03 10:51:43 by kahmada          ###   ########.fr       */
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