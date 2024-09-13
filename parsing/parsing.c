/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:34:41 by chourri           #+#    #+#             */
/*   Updated: 2024/09/11 20:45:33 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	symbols(int type_symbol)
// {
// 	return ((type_symbol == WORD || type_symbol == HEREDOC || type_symbol == REDIRECT_APPEND || type_symbol == REDIRECT_IN || type_symbol == REDIRECT_OUT || type_symbol == INSIDE_DOUBLE_QUOTE || type_symbol == INSIDE_SINGLE_QUOTE));
// }
// void	parse_error(char *msg)
// {
// 	printf("%s", msg);
// 	return ;
// }

// static char *remove_quotes1(char *data)
// {
// 	int len = ft_strlen(data);
// 	int start = 0;
// 	int end = len - 1;
// 	char *new;

// 	if (data[0] == '"' || data[0] == '\'')
// 	{
// 		char opening_quote = data[0];
// 		if (data[end] == opening_quote)
// 		{
// 			start++;
// 			end--;
// 		}
// 	}
// 	len = end - start + 1;
// 	new = malloc(len + 1);
// 	if (!new)
// 		return (NULL);
// 	int i = 0;
// 	while (i < len)
// 	{
// 		new[i] = data[start + i];
// 		i++;
// 	}
// 	new[len] = '\0';
// 	return (new);
// }

// int create_tempfile_error(char *temp_filename, int file_counter)
// {
// 	const char *base_filename = "tempfile_";
// 	char *counter_str;
// 	int tmp_fd;

// 	counter_str = ft_itoa(file_counter);
// 	if (!counter_str)
// 		return (-1);

// 	ft_strcpy(temp_filename, base_filename);
// 	ft_strcat(temp_filename, counter_str);
// 	ft_strcat(temp_filename, ".txt");
// 	free(counter_str);

// 	tmp_fd = open(temp_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
// 	if (tmp_fd == -1)
// 	{
// 		perror("open");
// 		return (-1);
// 	}
// 	return tmp_fd;
// }

// void handle_child_error(const char *limiter)
// {
// 	char *line;
// 	char *quoted_limiter;
// 	int tmp_fd;
// 	char temp_filename[256];

// 	tmp_fd = create_tempfile_error(temp_filename, 0);
// 	if (tmp_fd == -1)
// 		return ;
// 	quoted_limiter = remove_quotes1((char *)limiter);
// 	signal(SIGINT, signal_handler_heredoc);
// 	if (!quoted_limiter)
// 		return;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL)
// 			break;
// 		if (ft_strcmp(line, quoted_limiter) == 0)
// 		{
// 			printf("strcmp : %d\n", ft_strcmp(line, quoted_limiter));
// 			free(line);
// 			free(quoted_limiter);
// 			close(tmp_fd);
// 			return;
// 		}
// 		write(tmp_fd, line, strlen(line));
// 		write(tmp_fd, "\n", 1);
// 		free(line);
// 	}

// 	free(quoted_limiter);
// 	close(tmp_fd);
// }


// int	ft_protection(t_token *lst)
// {
// 	if (!lst)
// 		return (0);
// 	return (0);
// }
// int	pipe_parsing(t_token *lst)
// {
// 	t_token	*current;
// 	t_token	*fin;

// 	ft_protection(lst);
// 	current = lst;
// 	fin = last_token(lst);
// 	if (lst->type == PIPE)
// 		return (parse_error("syntax error near unexpected token `|'\n"), 1);
// 	else if (fin->type == PIPE)
// 		return (parse_error("syntax error: unexpected end of command after '|'\n"), 1);
// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 		{
// 			if (current->next == NULL || current->next->type == PIPE)
// 				return (parse_error("syntax error: multiple pipes with no command in between\n"), 1);
// 			current = current->next;
// 			while (current && (current->type == TAAB || current->type == SPAACE))
// 				current = current->next;
// 			if (current == NULL || !symbols(current->type))
// 				return (parse_error("syntax error: multiple pipes with no command in between\n"), 1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

// int redirect_in_parsing(t_token *lst)
// {
// 	t_token	*current;

// 	current = lst;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 		{
// 			current = current->next;
// 			while (current && current->data && (current->type == SPAACE || current->type == TAAB))
// 				current = current->next;
// 			if (current && (current->type == WORD || current->type == INSIDE_DOUBLE_QUOTE || current->type == INSIDE_SINGLE_QUOTE))
// 			{
// 				const char	*limiter = current->data;
// 				handle_child_error(limiter);
// 				current = current->next;
// 			}
// 		}
// 		if (current->type == REDIRECT_IN)
// 		{
// 			current = current->next;
// 			while (current && (current->type == TAAB || current->type == SPAACE))
// 				current = current->next;
// 			if (!current)
// 				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
// 			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
// 				return (parse_error("syntax error near unexpected token `<'\n"), 1);
// 			else if (current && current->type == REDIRECT_IN)
// 				return (parse_error("syntax error near unexpected token `<'\n"), 1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }


// int	redirect_out_parsing(t_token *lst)
// {
// 	t_token	*current;

// 	current = lst;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 		{
// 			current = current->next;
// 			while (current && (current->type == SPAACE || current->type == TAAB))
// 				current = current->next;
// 			if (current && (current->type == WORD || current->type == INSIDE_DOUBLE_QUOTE || current->type == INSIDE_SINGLE_QUOTE))
// 			{
// 				const char	*limiter = current->data;
// 				handle_child_error(limiter);
// 				current = current->next;
// 			}
// 		}
// 		if (current->type == REDIRECT_OUT)
// 		{
// 			current = current->next;
// 			while (current && (current->type == TAAB || current->type == SPAACE))
// 				current = current->next;
// 			if (!current)
// 				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
// 			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
// 				return (parse_error("syntax error near unexpected token `>'\n"), 1);
// 			else if (current && current->type == REDIRECT_OUT)
// 				return (parse_error("syntax error near unexpected token `>'\n"), 1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

// int	heredoc_parsing(t_token *lst)
// {
// 	t_token	*current;

// 	current = lst;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 		{
// 			current = current->next;
// 			while (current && (current->type == TAAB || current->type == SPAACE))
// 				current = current->next;
// 			if (!current)
// 				return (parse_error("syntax error near unexpected token `newline'\n"), 1);
// 			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
// 				return (parse_error("syntax error near unexpected token `<<'\n"), 1);
// 			else if (current && current->type == HEREDOC)
// 				return (parse_error("syntax error near unexpected token `<<'\n"), 1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }
// //perfect
// int	redirect_append(t_token *lst, char **envp)
// {
// 	t_token	*current;
// 	(void)envp;
// 	current = lst;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 		{
// 			current = current->next;
// 			while (current && current->data && (current->type == SPAACE || current->type == TAAB))
// 				current = current->next;
// 			if (current && (current->type == WORD || current->type == INSIDE_DOUBLE_QUOTE || current->type == INSIDE_SINGLE_QUOTE))
// 			{
// 				const char	*limiter = current->data;
// 				handle_child_error(limiter);
// 				current = current->next;
// 			}
// 		}
// 		if (current->type == REDIRECT_APPEND)
// 		{
// 			current = current->next;
// 			while (current && (current->type == TAAB || current->type == SPAACE))
// 				current = current->next;

// 			if (!current)
// 				return (parse_error("syntax error near unexpected token newline'\n"), 1);
// 			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
// 				return (parse_error("syntax error near unexpected token >>'\n"), 1);
// 			else if (current && current->type == REDIRECT_APPEND)
// 				return (parse_error("syntax error near unexpected token >>'\n"), 1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

// int	parse_quotes(char *s)
// {
// 	int is_quotes = 0;
// 	while (*s)
// 	{
// 		if (is_quotes == 0 && *s == '\'')
// 				is_quotes = 1;
// 		else if (is_quotes == 0 && *s == '\"')
// 			is_quotes = -1;
// 		else if (is_quotes == 1 && *s == '\'')
// 			is_quotes = 0;
// 		else if (is_quotes == -1 && *s == '\"')
// 			is_quotes = 0;
// 		s++;
// 	}
// 	if (is_quotes)
// 		return (parse_error("quote not closed\n"), is_quotes);
// 	return(is_quotes);
// }


// int parsing(t_token *lst, char **envp)
// {
// 	char	*ex;


// 	if (pipe_parsing(lst)  || heredoc_parsing(lst)
// 	|| redirect_append(lst, envp) || redirect_in_parsing(lst)
// 	|| redirect_out_parsing(lst))
// 	{
// 		ex = manage_exit_status(258, 1);
// 		free(ex);
// 		return (1);
// 	}
// 	return (0);
// }

int	symbols(int type_symbol)
{
	return ((type_symbol == WORD || type_symbol == HEREDOC || type_symbol == REDIRECT_APPEND || type_symbol == REDIRECT_IN || type_symbol == REDIRECT_OUT || type_symbol == INSIDE_DOUBLE_QUOTE || type_symbol == INSIDE_SINGLE_QUOTE));
}
int	ft_linked_list_search(t_token *lst)
{
	t_token *current = lst;
	while (current)
	{
		if (current->type == REDIRECT_APPEND || current->type == REDIRECT_IN || current->type == REDIRECT_OUT)
			return (1);
		current = current->next;
	}
	return (0);
}
void	parse_error(char *msg)
{
	printf("%s", msg);
	return ;
}

static char *remove_quotes1(char *data)
{
	int len = ft_strlen(data);
	int start = 0;
	int end = len - 1;
	char *new;

	if (data[0] == '"' || data[0] == '\'')
	{
		char opening_quote = data[0];
		if (data[end] == opening_quote)
		{
			start++;
			end--;
		}
	}
	len = end - start + 1;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	int i = 0;
	while (i < len)
	{
		new[i] = data[start + i];
		i++;
	}
	new[len] = '\0';
	return (new);
}

int create_tempfile_error(char *temp_filename, int file_counter)
{
	const char *base_filename = "tempfile_";
	char *counter_str;
	int tmp_fd;

	counter_str = ft_itoa(file_counter);
	if (!counter_str)
		return (-1);

	ft_strcpy(temp_filename, base_filename);
	ft_strcat(temp_filename, counter_str);
	ft_strcat(temp_filename, ".txt");
	free(counter_str);

	tmp_fd = open(temp_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmp_fd == -1)
	{
		perror("open");
		return (-1);
	}
	return tmp_fd;
}

void handle_child_error(const char *limiter)
{
	char *line;
	char *quoted_limiter;
	int tmp_fd;
	char temp_filename[256];

	tmp_fd = create_tempfile_error(temp_filename, 0);
	if (tmp_fd == -1)
		return ;
	quoted_limiter = remove_quotes1((char *)limiter);
	signal(SIGINT, signal_handler_heredoc);
	if (!quoted_limiter)
		return;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (ft_strcmp(line, quoted_limiter) == 0)
		{
			free(line);
			free(quoted_limiter);
			close(tmp_fd);
			return;
		}
		write(tmp_fd, line, strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}

	free(quoted_limiter);
	close(tmp_fd);
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
		if (current->type == HEREDOC && lst->flag == 0 && ft_linked_list_search(lst))
		{
			current = current->next;
			while (current && current->data && (current->type == SPAACE || current->type == TAAB))
				current = current->next;
			if (current && (current->type == WORD || current->type == INSIDE_DOUBLE_QUOTE || current->type == INSIDE_SINGLE_QUOTE))
			{
				const char	*limiter = current->data;
				handle_child_error(limiter);
				lst->flag = 1;
				current = current->next;
			}
		}
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
		if (current->type == HEREDOC && lst->flag == 0 && ft_linked_list_search(lst))
		{
			current = current->next;
			while (current && (current->type == SPAACE || current->type == TAAB))
				current = current->next;
			if (current && (current->type == WORD || current->type == INSIDE_DOUBLE_QUOTE || current->type == INSIDE_SINGLE_QUOTE))
			{
				const char	*limiter = current->data;
				handle_child_error(limiter);
				lst->flag = 1;
				current = current->next;
			}
		}
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
//perfect
int	redirect_append(t_token *lst, char **envp)
{
	t_token	*current;
	(void)envp;
	current = lst;
	while (current)
	{
		if (current->type == HEREDOC && lst->flag == 0 && ft_linked_list_search(lst))
		{
			current = current->next;
			while (current && current->data && (current->type == SPAACE || current->type == TAAB))
				current = current->next;
			if (current && (current->type == WORD || current->type == INSIDE_DOUBLE_QUOTE || current->type == INSIDE_SINGLE_QUOTE))
			{
				const char	*limiter = current->data;
				handle_child_error(limiter);
				lst->flag = 1;
				current = current->next;
			}
		}
		if (current->type == REDIRECT_APPEND)
		{
			current = current->next;
			while (current && (current->type == TAAB || current->type == SPAACE))
				current = current->next;

			if (!current)
				return (parse_error("syntax error near unexpected token newline'\n"), 1);
			else if (current->type != WORD && current->type != INSIDE_DOUBLE_QUOTE && current->type != INSIDE_SINGLE_QUOTE)
				return (parse_error("syntax error near unexpected token >>'\n"), 1);
			else if (current && current->type == REDIRECT_APPEND)
				return (parse_error("syntax error near unexpected token >>'\n"), 1);
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


int parsing(t_token *lst, char **envp)
{
	char	*ex;


	if (pipe_parsing(lst)  || heredoc_parsing(lst)
	|| redirect_append(lst, envp) || redirect_in_parsing(lst)
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
