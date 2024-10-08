/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:08:45 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/08 20:40:43 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token *lst)
{
	t_token	*current;
	t_token	*next;

	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}

static char	*pre_conv(int len)
{
	char	*tmp;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	return (tmp);
}

static int	int_len(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*result;
	long	nbr;

	nbr = n;
	len = int_len(nbr);
	result = pre_conv(len);
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	i = len - 1;
	if (nbr == 0)
		result[i] = '0';
	while (nbr != 0)
	{
		result[i--] = ((nbr % 10) + 48);
		nbr = nbr / 10;
	}
	result[len] = '\0';
	return (result);
}
