/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:19:15 by chourri           #+#    #+#             */
/*   Updated: 2024/10/09 19:34:27 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;

	i = -1;
	if (!s1)
		return (ft_strdup(s2));
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!new_s)
		exit(1);
	while (s1[++i])
		new_s[i] = s1[i];
	new_s[i++] = ' ';
	j = 0;
	while (s2[j])
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	return (new_s);
}

int	is_redirection_symbol(int type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_IN
		|| type == REDIRECT_OUT || type == PIPE || type == HEREDOC);
}

void	ft_lstadd_back_new(t_token **lst, t_type type, const char *data)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return ;
	new_token->data = ft_strdup(data);
	if (new_token->data == NULL)
	{
		free(new_token);
		return ;
	}
	new_token->type = type;
	new_token->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_token;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_token;
}

t_token	*free_list(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list->next;
		free(list->data);
		free(list);
		list = temp;
	}
	return (NULL);
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*temp;

	while (cmd_list)
	{
		free_word_array(cmd_list->args);
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp);
	}
}
