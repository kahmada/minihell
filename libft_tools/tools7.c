/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:05:48 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/15 19:06:11 by kahmada          ###   ########.fr       */
=======
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:19:15 by chourri           #+#    #+#             */
/*   Updated: 2024/09/17 11:21:37 by chourri          ###   ########.fr       */
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + start, len);
	trimmed[len] = '\0';
	return (trimmed);
}
=======
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

void ft_lstadd_back_new(t_token **lst, t_type type, const char *data)
{
	t_token *new_token;
	t_token *last;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return;

	new_token->data = strdup(data);
	if (new_token->data == NULL)
	{
		free(new_token);
		return;
	}
	new_token->type = type;
	new_token->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_token;
		return;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_token;
}

t_token *free_list(t_token *list)
{
	t_token *temp;

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
	int			i;

	while (cmd_list)
	{
		free_word_array(cmd_list->args);
		// if (cmd_list->infile)
		// 	free(cmd_list->infile);
		// if (cmd_list->outfile)
		// 	free(cmd_list->outfile);
		if (cmd_list->envp)
		{
			i = 0;
			// while (cmd_list->envp[i])
			// {
			// 	free(cmd_list->envp[i]);
			// 	i++;
			// }
			// free(cmd_list->envp);
		}
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp);
	}
}
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
