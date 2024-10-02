/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:00 by chourri           #+#    #+#             */
/*   Updated: 2024/10/02 19:01:44 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	dest_len;
	int	i;

	dest_len = 0;
	i = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_token	*last_token(t_token *head)
{
	t_token	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

t_token	*ft_lstnew(char *data, t_type type)
{
	t_token	*element;

	element = (t_token *)malloc(sizeof(t_token));
	if (!element)
		return (NULL);
	element->data = data;
	element->type = type;
	element->next = NULL;
	element->previous = NULL;
	return (element);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*p;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next != NULL)
		p = p->next;
	p->next = new;
	new->previous = p;
}

const char*	get_token_type_name(t_type type)
{
	switch (type)
	{
		case COMMAND:
			return "COMMAND";
		case ARGUMENT:
			return "ARGUMENT";
		case PIPE:
			return "PIPE";
		case REDIRECT_IN:
			return "REDIRECT_IN";
		case REDIRECT_OUT:
			return "REDIRECT_OUT";
		case REDIRECT_APPEND:
			return "REDIRECT_APPEND";
		case HEREDOC:
			return "HEREDOC";
		case ENV_VAR:
			return "ENV_VAR";
		case EXIT_STATUS:
			return "EXIT_STATUS";
		case INSIDE_SINGLE_QUOTE:
			return "INSIDE_SINGLE_QUOTE";
		case INSIDE_DOUBLE_QUOTE:
			return "INSIDE_DOUBLE_QUOTE";
		case WORD:
			return "WORD";
		// case END:
		// 	return "END";
		// case ERROR:
		// 	return "ERROR";
		case DS:
			return "DS";
		case SPAACE :
			return "SPACE";
		case TAAB :
			return "TAB";
		default:
			return "UNKNOWN";
	}
}

void	print_list(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current && current->data && current->type)
	{
		printf("Type: %s, Data: {%s}\n",
			get_token_type_name(current->type), current->data);
		current = current->next;
	}
}
