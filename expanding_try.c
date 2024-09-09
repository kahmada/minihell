/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_try.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/09/06 18:42:16 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
}
int	is_digit(char c)
{
	return (c >= '1' && c <= '9');
}
void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

typedef struct s_data
{
	//expanding_var
	int		i;
	int		var_len;
	char	*start;
	char	*var;
	size_t	exp_len;
	char	*exp;
	char	*ptr;
	char	*value;
	char	*name;
	int		is_home;
	char	*data;
}			t_data;
//libft_tools
char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*dup;

	dup = malloc(n + 1);
	i = 0;
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return  ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
//expand $0 $5678 $-
char *allocate_for_special_exp(char *data)
{
	char *temp_data;
	char *new;

	temp_data = strchr(data, '$');
	if (temp_data && *(temp_data + 1) == '0')
		new = malloc(strlen(data) + 4); // Extra space for "bash"
	else if (temp_data && is_digit(*(temp_data + 1)))
		new = malloc(strlen(data)); // Skip one character for the digit
	else if (temp_data && *(temp_data + 1) == '-')
		new = malloc(strlen(data) + 5); // Extra space for "himBH"
	else
		new = ft_strdup(data);
	if (!new)
		return (NULL);
	return new;
}
int	handle_zero(char **data, char **new_ptr)
{
	if (**data == '$' && *(*data + 1) == '0')
	{
		strcpy(*new_ptr, "bash");
		(*new_ptr) += 4;
		*data += 2;
		return (1);
	}
	return (0);
}
char *handle_digit_after_dollar_sign(char *data)
{
	char *new;
	char *new_ptr;

	new = allocate_for_special_exp(data);
	if (!new || !data)
		return NULL;
	new_ptr = new;
	while (*data)
	{
		if (handle_zero(&data, &new_ptr))
			continue; //we skip here the rest of the loop if it's handled by handle_zero
		if (*data == '$' && *(data + 1) == '-')
		{
			strcpy(new_ptr, "himBH");
			new_ptr += 5;
			data += 2;
		}
		else if (*data == '$' && is_digit(*(data + 1)))
			data += 2;
		else
			*new_ptr++ = *data++;
	}
	*new_ptr = '\0';
	return new;
}

//handle this :
//// $*
//$^
//$$USER ASK ABOUT THIS
//$USER"'"
//$-HHH
//$? Should stay the same 'exit status'


static void	process_variable_expansion(char **data, t_data *mydata, char **envp)
{
	mydata->start = *data;
	while (**data && **data != ' ' && **data != '$' && isalnum(**data))
		(*data)++;
	mydata->var_len = *data - mydata->start;
	mydata->var = ft_strndup(mydata->start, mydata->var_len);
	mydata->i = 0;
	while (envp[mydata->i])
	{
		if (ft_strncmp(envp[mydata->i], mydata->var, mydata->var_len) == 0 && envp[mydata->i][mydata->var_len] == '=')
		{
			mydata->exp_len += ft_strlen(envp[mydata->i] + mydata->var_len + 1); // Skip the name of the variable
			break;
		}
		mydata->i++;
	}
	free(mydata->var);
}
static size_t	expanded_len(char *data, char **envp)
{
	t_data	mydata;

	mydata.exp_len = 0;
	while (*data)
	{
		if (*data == '$')
		{
			data++;
			process_variable_expansion(&data, &mydata, envp);
		}
		else
		{
			mydata.exp_len++;
			data++;
		}
	}
	return (mydata.exp_len);
}
void	special_cases_exp(t_data **mydata,char *data, char **envp)
{
	if (data[0] == '~')
	{
		(*mydata)->name = getenv("HOME");
		if (!(*mydata)->name)
			(*mydata)->name = "";
		(*mydata)->exp_len = ft_strlen((*mydata)->name) + ft_strlen(data + 1);

	}
	else
		(*mydata)->exp_len = expanded_len(data, envp);
	(*mydata)->exp = malloc((*mydata)->exp_len + 1);
}
char *expand_variable(char *data, char **envp)
{
	// size_t exp_len;
	// char *exp;
	// char *ptr;
	// const char *start;
	// int var_len;
	// char *var;
	// char *value;
	// char *name = NULL;
	// int i;
	t_data	*mydata;
	// if (data[0] == '~')
	// {
	// 	mydata.name = getenv("HOME");
	// 	if (!mydata.name)
	// 		mydata.name = "";
	// 	mydata.exp_len = ft_strlen(mydata.name) + ft_strlen(data + 1);
	// }
	// else
	// 	mydata.exp_len = expanded_len(data, envp);
	// mydata.exp = malloc(mydata.exp_len + 1);
	special_cases_exp(&mydata, data, envp);
	mydata->ptr = mydata->exp;
	if (mydata->exp == NULL)
		return NULL;

	if (*data == '~')
	{
		mydata->name = getenv("HOME");
		if (!mydata->name)
			mydata->name = "";
		strcpy(mydata->ptr, mydata->name);
		mydata->ptr += ft_strlen(mydata->name);
		data++;
	}
	while (*data)
	{
		if (*data == '$')
		{
			data++;
			mydata->start = data;
			while (*data && !isspace(*data) && *data != '$' && *data != '~' && (is_alnum(*data) || *data == '_'))
				data++;
			mydata->var_len = data - mydata->start;
			mydata->var = malloc(mydata->var_len + 1);
			if (!mydata->var)
				return NULL;
			strncpy(mydata->var, mydata->start, mydata->var_len);
			mydata->var[mydata->var_len] = '\0';
			mydata->i = 0;
			mydata->value = "";
			while (envp[mydata->i])
			{
				if (strncmp(envp[mydata->i], mydata->var, mydata->var_len) == 0 && envp[mydata->i][mydata->var_len] == '=')
				{
					mydata->value = envp[mydata->i] + mydata->var_len + 1;
					break;
				}
				(mydata->i)++;
			}
			strcpy(mydata->ptr, mydata->value);
			mydata->ptr += ft_strlen(mydata->value);
			free(mydata->var);
		}
		else
			*(mydata->ptr)++ = *data++;
	}
	*(mydata->ptr) = '\0';
	return (mydata->exp);
}


void	handle_dollar(t_token *token, char **envp)
{
	char	*var_name;
	char	*expanded;

	// if (!(token->next) && ft_strcmp(token->data, "*") == 0)
	// {
	// 	token->data = ft_strdup("Makefile");
	// 	printf("Makefile =  %p", token->data);
	// 	return ;
	// }
	while (token && token->data)
	{
		if (token->data[0] != '\'')
		{
			// printf("HEY1\n");
			token->data = handle_digit_after_dollar_sign(token->data);
		}
		if ((token->data[0] == '~' && token->data[1] == '/') || (token->data[0] == '~' && token->data[1] == '\0'))
		{
			// printf("HEY2\n");
			expanded = expand_variable(token->data, envp);
			free(token->data);
			token->data = expanded;
		}
		else if ((ft_strcmp(token->data,"$*") == 0 || ft_strcmp(token->data, "\"$*\"") == 0 || ft_strcmp(token->data, "$!") == 0 || ft_strcmp(token->data, "\"$!\"") == 0) && token->data[0] != '\'')
		{
			// printf("HEY3\n");
			free(token->data);
			token->data = strdup("\n");
		}
		else if (token->type == EXIT_STATUS || token->type == DS || ft_strcmp(token->data, "$^") == 0 || ft_strcmp(token->data, "\"$^\"") == 0)
		{
			// printf("HEY4\n");
			printf("%s", token->data);
			token = token->next;
		}
		else if (token->data[0] != '"' && ft_strchr(token->data, '$') && token->data[0] != '\'')
		{
			// printf("HEY5\n");
			expanded = expand_variable(token->data, envp);
			free(token->data);
			token->data = expanded;
		}
		else if (token->data[0] == '"' && ft_strchr(token->data, '$'))
		{
			// printf("HEY6\n");
			var_name = ft_strdup(token->data);
			free(token->data);
			token->data = var_name;
			expanded = expand_variable(token->data, envp);
			free(token->data);
			token->data = expanded;
		}
		else if (token->data[0] == '\'' && ft_strchr(token->data, '$'))
		{
			// printf("HEY7\n");
			var_name = ft_strdup(token->data);
			free(token->data);
			token->data = var_name;
		}
		if (token)
			token = token->next;
		printf("data : %s\n", token->data);
	}
	// printf("\n");
}
//to handle
//echo $""


//heredoc + exp
// if (flag && ft_strchr(line, '$'))
// 			line = expand_variable(line, envp);
	// int	flag = 1;
	// if (ft_strchr((char *)limiter, '\'') || ft_strchr((char *)limiter, '"'))
	// 	flag = 0;
