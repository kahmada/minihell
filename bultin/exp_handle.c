/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:36:56 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/30 19:54:19 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_invalid_identifier(char **key, char **value)
{
	fprintf(stderr, "minishell: export: `%s`:not a valid identifier\n", *key);
	free(*key);
	*key = NULL;
	*value = NULL;
}

// void	valid_and_prs_exprt(const char *arg, char **ky, char **val, int *ap_md)
// {
// 	*ap_md = 0;
// 	*ky = ft_strdup(arg);
// 	if ((*ky)[0] == '=' || (*ky)[0] == '$' || ft_strchr(*ky, '=') == *ky)
// 	{
// 		handle_invalid_identifier(ky, val);
// 		return ;
// 	}
// 	*val = ft_strchr(*ky, '=');//=......
// 	if (!*val || *(*val + 1) == '\0')
// 	{
// 		*val = NULL;
// 		return ;
// 	}
// 	**val = '\0';//\0
// 	(*val)++;//value
// 	if ((*ky)[ft_strlen(*ky) - 1] == '+')
// 	{
// 		*ap_md = 1;
// 		(*ky)[ft_strlen(*ky) - 1] = '\0';
// 	}
// 	if (!is_valid_variable_name(*ky))
// 		handle_invalid_identifier(ky, val);
// }
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

void	valid_and_prs_exprt(const char *arg, char **ky, char **val, int *ap_md)
{
    *ap_md = 0;
    *val = ft_strchr(arg, '=');
    if (*val)
    {
        *ky = ft_substr(arg, 0, *val - arg);
        (*val)++; // Move past the '=' to get the value
		if (*val && **val == '\0')
			*val = ft_strdup(" ");
    }
    else
    {
        *ky = ft_strdup(arg);
        *val = NULL;
    }
    if ((*ky)[0] == '=' || (*ky)[0] == '$' || ft_strchr(*ky, '=') == *ky)
    {
        handle_invalid_identifier(ky, val);
        return;
    }
    if ((*ky)[ft_strlen(*ky) - 1] == '+')
    {
        *ap_md = 1;
        (*ky)[ft_strlen(*ky) - 1] = '\0'; // Remove the '+' from the key
    }
    if (!is_valid_variable_name(*ky))
    {
        handle_invalid_identifier(ky, val);
        return;
    }
    if (*val && **val == '\0')
        *val = NULL;
}
