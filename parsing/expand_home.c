/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:19:23 by chourri           #+#    #+#             */
/*   Updated: 2024/10/06 13:20:42 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_home_dir(char *data)
{
	char	*home;
	char	*expanded;
	size_t	exp_len;

	if (data[0] == '~' && (data[1] == '/' || data[1] == '\0'))
	{
		home = getenv("HOME");
		if (!home)
			return (ft_strdup(data));
		exp_len = ft_strlen(home) + ft_strlen(data + 1);
		expanded = malloc(exp_len + 1);
		if (!expanded)
			return (NULL);
		ft_strcpy(expanded, home);
		ft_strcat(expanded, data + 1);
		return (expanded);
	}
	return (ft_strdup(data));
}

void	expand_home(t_token *token)
{
	char	*expanded;

	if ((token->data[0] == '~' && token->data[1] == '/')
		|| (token->data[0] == '~' && token->data[1] == '\0'))
	{
		expanded = expand_home_dir(token->data);
		free(token->data);
		token->data = expanded;
	}
}
