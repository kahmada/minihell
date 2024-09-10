/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:41 by chourri           #+#    #+#             */
/*   Updated: 2024/09/10 17:49:25 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	symbols(int type_symbol)
{
	return ((type_symbol == WORD || type_symbol == HEREDOC || type_symbol == REDIRECT_APPEND || type_symbol == REDIRECT_IN || type_symbol == REDIRECT_OUT || type_symbol == INSIDE_DOUBLE_QUOTE || type_symbol == INSIDE_SINGLE_QUOTE));
}

void	parse_error(char *msg)
{
	printf("%s\n", msg);
	return ;
}
int	ft_protection(t_token *lst)
{
	if (!lst)
		return (0);
	return (0);
}
int	pipe_parsing(t_token *lst)
{
	t_token	*current;
	t_token	*fin;

	ft_protection(lst);
	current = lst;
	fin = last_token(lst);
	if (lst->type == PIPE)
		return (parse_error("syntax error near unexpected token `|'\n"), 1);
	else if (fin->type == PIPE)
		return (parse_error("syntax error: unexpected end of command after '|'\n"), 1);
	while (current)
	{
		if (current->type == PIPE)
		{
			if (current->next == NULL || current->next->type == PIPE)
				return (parse_error("syntax error: multiple pipes with no command in between\n"), 1);
			current = current->next;
			while (current && (current->type == TAAB || current->type == SPAACE))
				current = current->next;
			if (current == NULL || !symbols(current->type))
				return (parse_error("syntax error: multiple pipes with no command in between\n"), 1);
		}
		current = current->next;
	}
	return (0);
}

int redirect_in_parsing(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			current = current->next;
			while (current && (current->type == TAAB || current->type == SPAACE))
				current = current->next;
			if (!current)
				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
				return (parse_error("syntax error near unexpected token `<'\n"), 1);
			else if (current && current->type == REDIRECT_IN)
				return (parse_error("syntax error near unexpected token `<'\n"), 1);
		}
		current = current->next;
	}
	return (0);
}


int	redirect_out_parsing(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current)
	{
		if (current->type == REDIRECT_OUT)
		{
			current = current->next;
			while (current && (current->type == TAAB || current->type == SPAACE))
				current = current->next;
			if (!current)
				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
				return (parse_error("syntax error near unexpected token `>'\n"), 1);
			else if (current && current->type == REDIRECT_OUT)
				return (parse_error("syntax error near unexpected token `>'\n"), 1);
		}
		current = current->next;
	}
	return (0);
}

int	heredoc_parsing(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			current = current->next;
			while (current && (current->type == TAAB || current->type == SPAACE))
				current = current->next;
			if (!current)
				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
				return (parse_error("syntax error near unexpected token `<<'\n"), 1);
			else if (current && current->type == HEREDOC)
				return (parse_error("syntax error near unexpected token `<<'\n"), 1);
		}
		current = current->next;
	}
	return (0);
}

//finish the rest starting here
int	redirect_append(t_token *lst)
{
		t_token	*current;

	current = lst;
	while (current)
	{
		if (current->type == REDIRECT_APPEND)
		{
			current = current->next;
			while (current && (current->type == TAAB || current->type == SPAACE))
				current = current->next;
			if (!current)
				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
				return (parse_error("syntax error near unexpected token `>>'\n"), 1);
			else if (current && current->type == REDIRECT_APPEND)
				return (parse_error("syntax error near unexpected token `>>'\n"), 1);
		}
		current = current->next;
	}
	return (0);
}


int	parse_quotes(char *s)
{
	int is_quotes = 0;
	while (*s)
	{
		if (is_quotes == 0 && *s == '\'')
				is_quotes = 1;
		else if (is_quotes == 0 && *s == '\"')
			is_quotes = -1;
		else if (is_quotes == 1 && *s == '\'')
			is_quotes = 0;
		else if (is_quotes == -1 && *s == '\"')
			is_quotes = 0;
		s++;
	}
	if (is_quotes)
		return (parse_error("quote not closed\n"), is_quotes);
	return(is_quotes);
}


int parsing(t_token *lst)
{
	char	*ex;
	if (pipe_parsing(lst)  || heredoc_parsing(lst)
	|| redirect_append(lst) || redirect_in_parsing(lst)
	|| redirect_out_parsing(lst))
	{
		ex = manage_exit_status(258, 1);
		free(ex);
		return (1);
	}
	return (0);
}

// int	double_single_quotes_parsing(t_token *lst)
// {
// 	t_token	*current = lst;
// 	size_t	i;

// 	int	dq_open = 0;
// 	int	sq_open = 0;
// 	while (current)
// 	{
// 		i = 0;
// 		while (i < strlen(current->data))
// 		{
// 			if (current->data[i] == '"')
// 				dq_open = !dq_open;
// 			else if (current->data[i] == '\'')
// 				sq_open = !sq_open;
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	if (dq_open)
// 		return (parse_error("Error: Double quotes are not closed\n"), 1);
// 	if (sq_open)
// 		return (parse_error("Error: Single quotes are not closed\n"), 1);
// 	return (0);
// }

// int	parse_quotes(char *input)
// {
// 	int count_sq;
// 	int	count_dq;

// 	count_dq = 0;
// 	count_sq = 0;
// 	while (*input)
// 	{
// 		if (*input == '"')
// 			count_dq++;
// 		else if (*input == '\'')
// 			count_sq++;
// 		input++;
// 	}
// 	if ((count_dq % 2 != 0) || (count_sq % 2 != 0))
// 		return (parse_error("Error: Quotes are not closed\n"), 1);
// 	return (0);
// }

//                          "'"'"
//1 : is_quote = ";
// input[i] = ";
// is_quote = 0;

// int	parse_quotes(char *input)
// {
// 	int i = 0;
// 	char	is_quote = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"' || input[i] == '\'')
// 		{
// 			is_quote = input[i];
// 			while (input[i] && input[i] != is_quote)
// 				i++;
// 			printf("is_quote = %c\n", is_quote);
// 			if (input[i] != is_quote)
// 				return (1);
// 			is_quote = 0;
// 		}
// 		i++;
// 	}
// 	return (0);
// }


// int parse_quotes(char *input)
// {
// 	int	is_opened = 0;
// 	int	is_closed = 0;
// 	int	i = 0;

// 	while (input)
// }
// int	double_single_quotes_parsing(char *input)
// {
// 	int count_sq;
// 	int	count_dq;

// 	count_dq = 0;
// 	count_sq = 0;
// 	while (*input)
// 	{
// 		if (*input == '"')
// 			count_dq++;
// 		else if (*input == '\'')
// 			count_sq++;
// 		input++;
// 	}
// 	if ((count_dq % 2 != 0) || (count_sq % 2 != 0))
// 		return (parse_error("Error: Quotes are not closed\n"), 1);
// 	return (0);
// }
