/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_new_token_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:40:03 by chourri           #+#    #+#             */
/*   Updated: 2024/09/05 11:29:10 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <stdlib.h>
#include <string.h>

void join_token_data(char **current_data, t_token *token)
{
    char *temp;

    if (token->type == REDIRECT_APPEND || token->type == REDIRECT_IN ||
        token->type == REDIRECT_OUT || token->type == HEREDOC)
    {
        temp = malloc(strlen(*current_data) + strlen(token->data) + 3);
        if (!temp)
            return;
    }
    else
    {
        temp = malloc(strlen(*current_data) + strlen(token->data) + 1);
        if (!temp)
            return;
        strcpy(temp, *current_data);
        strcat(temp, token->data);
    }
    free(*current_data);
    *current_data = temp;
}

void build_new_token_list(t_token *tokens, t_token **new_list)
{
    t_token *current = tokens;
    t_token *new_token = NULL;
    char *current_data = NULL;

    while (current)
    {
        if (current->type == PIPE)
        {
            if (current_data)
            {
                ft_lstadd_back(new_list, WORD, strdup(current_data));
                free(current_data);
                current_data = NULL;
            }
            current = current->next;
            continue;
        }

        if (!current_data)
        {
            current_data = strdup(current->data);
        }
        else
            join_token_data(&current_data, current);
        current = current->next;
    }

    if (current_data)
    {
        ft_lstadd_back(new_list, WORD, strdup(current_data));
        free(current_data);
    }
}
