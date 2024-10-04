/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:36:56 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/04 17:59:15 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_invalid_identifier(char **key, char **value)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(*key , 2);
	ft_putstr_fd(":not a valid identifier\n", 2);
	free(*key);
	*key = NULL;
	*value = NULL;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*kast;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	kast = (char *)malloc((len + 1) * sizeof(char));
	if (!kast)
		return (NULL);
	while (s[start] && i < len)
	{
		kast[i++] = s[start++];
	}
	kast[i] = '\0';
	return (kast);
}

void	extract_key_value(const char *arg, char **ky, char **val)
{
	*val = ft_strchr(arg, '=');
	if (*val)
	{
		*ky = ft_substr(arg, 0, *val - arg);
		(*val)++;
		if (*val && **val == '\0')
			*val = NULL;
	}
	else
	{
		*ky = ft_strdup(arg);
		*val = NULL;
	}
}

void	valid_and_prs_exprt(const char *arg, char **ky, char **val, int *ap_md)
{
	char	*ex;

	*ap_md = 0;
	extract_key_value(arg, ky, val);
	if ((*ky)[0] == '=' || (*ky)[0] == '$' || ft_strchr(*ky, '=') == *ky)
	{
		handle_invalid_identifier(ky, val);
		ex = manage_exit_status(1, 1);
		return ;
	}
	if ((*ky)[ft_strlen(*ky) - 1] == '+')
	{
		*ap_md = 1;
		(*ky)[ft_strlen(*ky) - 1] = '\0';
	}
	if (!is_valid_variable_name(*ky))
	{
		handle_invalid_identifier(ky, val);
		ex = manage_exit_status(1, 1);
		return ;
	}
	if (*val && **val == '\0')
		*val = NULL;
}
