/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/09/10 19:01:41 by chourri          ###   ########.fr       */
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


// char *handle_digit_after_dollar_sign(char *data)
// {
// 	char *new;
// 	char *temp_data;

// 	if (!data)
// 		return NULL;
// 	temp_data = ft_strchr(data, '$');
// 	if (temp_data && *(temp_data + 1) == '0' )
// 	{
// 		new = malloc(strlen(data) + 4);
// 		if (!new)
// 			return NULL;
// 	}
// 	else if (temp_data && is_digit(*(temp_data + 1)))
// 	{
// 		new = malloc(strlen(data));
// 		if (!new)
// 			return NULL;
// 	}
// 	else if (temp_data && *(temp_data + 1) == '-')
// 	{
// 		new = malloc(strlen(data) + 5);
// 		if (!new)
// 			return (NULL);
// 	}
// 	else
// 	{
// 		return (data);
// 	}
// 	char *new_ptr = new;
// 	while (*data)
// 	{
// 		if (*data == '$' && *(data + 1) == '0')
// 		{
// 			strcpy(new_ptr, "bash");
// 			new_ptr += 4;
// 			data += 2;
// 		}
// 		else if (*data == '$' && *(data + 1) == '-')
// 		{
// 			strcpy(new_ptr, "himBH");
// 			new_ptr += 5;
// 			data += 2;
// 		}
// 		else if (*data == '$' && is_digit(*(data + 1)))
// 			data += 2;
// 		else
// 			*new_ptr++ = *data++;
// 	}
// 	*new_ptr = '\0';
// 	return (new);
// }

// static size_t	expanded_len(char *data, char **envp)
// {
// 	size_t	exp_len;
// 	char	*start;
// 	int		var_len;
// 	char	*var;
// 	int		i;

// 	exp_len = 0;
// 	while (*data)
// 	{
// 		if (*data == '$')
// 		{
// 			data++;
// 			start = data;
// 			while (*data && *data != ' ' && *data != '$' && is_alnum(*data))
// 				data++;
// 			var_len = data - start;
// 			var = ft_strndup(start, var_len);
// 			i = 0;
// 			while (envp[i])
// 			{
// 				if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
// 				{
// 					exp_len += ft_strlen(envp[i] + var_len + 1);
// 					break ;
// 				}
// 				i++;
// 			}
// 			free(var);
// 		}
// 		else
// 		{
// 			exp_len++;
// 			data++;
// 		}
// 	}
// 	return (exp_len);
// }
// char *expand_variable(char *data, char **envp)
// {
// 	size_t exp_len;
// 	char *exp;
// 	char *ptr;
// 	const char *start;
// 	int var_len;
// 	char *var;
// 	char *value;
// 	char *name = NULL;
// 	int i;
// 	int	is_home = 0;

// 	if (data[0] == '~')
// 	{
// 		char *name = getenv("HOME");
// 		exp_len = ft_strlen(name) + ft_strlen(data + 1);
// 		exp = malloc(exp_len + 1);
// 	}
// 	else
// 	{
// 		exp_len = expanded_len(data, envp);
// 		exp = malloc(exp_len + 1);
// 	}
// 	ptr = exp;
// 	while (*data)
// 	{
// 		if (*data == '$' || *data == '~')
// 		{
// 			if (*data == '~')
// 			{
// 				is_home = 1;
// 				name = getenv("HOME");
// 			}
// 			data++;
// 			start = data;
// 			while (*data && *data != ' ' && *data != '$' && *data != '~' && is_alnum(*data))
// 				data++;
// 			var_len = data - start;
// 			var = ft_strndup(start, var_len);
// 			i = 0;
// 			value = "";
// 			if (is_home)
// 				value = name;
// 			while (envp[i])
// 			{
// 				if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
// 				{
// 					value = envp[i] + var_len + 1;
// 					break;
// 				}
// 				i++;
// 			}
// 			strcpy(ptr, value);
// 			ptr += ft_strlen(value);
// 			free(var);
// 		}
// 		else
// 			*ptr++ = *data++;
// 	}
// 	*ptr = '\0';
// 	return exp;
// }


static size_t expanded_len(char *data, char **envp)
{
	size_t exp_len = 0;
	char *start;
	int var_len;
	char *var;
	int i;

	while (*data)
	{
		if (*data == '$')
		{
			data++;
			if (*data == '0' || *data == '-')
			{
				if (*data == '0')
					exp_len += 4; // "bash"
				else if (*data == '-')
					exp_len += 5; // "himBH"
				data++;
			}
			else if (isdigit(*data))
				data++;
			else
			{
				start = data;
				while (*data && *data != ' ' && *data != '$' && is_alnum(*data))
					data++;
				var_len = data - start;
				var = strndup(start, var_len);
				i = 0;
				while (envp[i])
				{
					if (strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
					{
						exp_len += strlen(envp[i] + var_len + 1);
						break;
					}
					i++;
				}
				free(var);
			}
		} else
		{
			exp_len++;
			data++;
		}
	}
	return exp_len;
}

char *expand_variable(char *data, char **envp)
{
	size_t exp_len;
	char *exp;
	char *ptr;
	const char *start;
	int var_len;
	char *var;
	char *value;
	int i;

	exp_len = expanded_len(data, envp);
	exp = malloc(exp_len + 1);
	if (!exp)
		return NULL;

	ptr = exp;
	while (*data)
	{
		if (*data == '$')
		{
			data++;
			if (*data == '0')
			{
				strcpy(ptr, "bash");
				ptr += 4;
				data++;
			} else if (*data == '-')
			{
				strcpy(ptr, "himBH");
				ptr += 5;
				data++;
			}
			else if (isdigit(*data))
				data++;
			else
			{
				start = data;
				while (*data && *data != ' ' && *data != '$' && is_alnum(*data))
					data++;
				var_len = data - start;
				var = strndup(start, var_len);
				i = 0;
				value = "";
				while (envp[i])
				{
					if (strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
					{
						value = envp[i] + var_len + 1;
						break;
					}
					i++;
				}
				strcpy(ptr, value);
				ptr += strlen(value);
				free(var);
			}
		}
		else
			*ptr++ = *data++;
	}
	*ptr = '\0';
	return exp;
}

int	check_heredoc_presence(t_token *token)
{
	int is_heredoc = 0;
			if (token)
		{
			token = token->previous;
			while (token && token->type != HEREDOC)
			{
				token = token->previous;
			}
			if (token && token->type == HEREDOC)
				is_heredoc = 1;
			else
				is_heredoc = 0;
		}
	return (is_heredoc);
}
void	ft_expand(t_token *token, char **envp)
{
	char	*var_name;
	char	*expanded;
	(void)envp;
	while (token && token->data)
	{
		if (token && token->data && token->data[0] != '\'' && !check_heredoc_presence(token) && token->type != DS)
		{
			if (token->data && token->type == EXIT_STATUS)
			{
				expanded = manage_exit_status(0, 0);
				free(token->data);
				token->data = expanded;
			}
			else if (((token->data[0] == '~' && token->data[1] == '/') || (token->data[0] == '~' && token->data[1] == '\0')) && token->type != EXIT_STATUS)
			{
				expanded = expand_variable(token->data, envp); //no leaks inside
				free(token->data);
				token->data = expanded;
			}
			else if ((ft_strcmp(token->data,"$*") == 0 || ft_strcmp(token->data, "\"$*\"") == 0 || ft_strcmp(token->data, "$!") == 0 || ft_strcmp(token->data, "\"$!\"") == 0) && token->data[0] != '\'' && token->type != EXIT_STATUS)
			{
				free(token->data);
				token->data = strdup("\n"); //no leaks inside
			}
			else if (token->data[0] != '"' && ft_strchr(token->data, '$') && token->type != EXIT_STATUS && token->data[0] != '\'')
			{
				expanded = expand_variable(token->data, envp);
				free(token->data);
				token->data = expanded; //NO leaks
			}
			else if (token->data[0] == '"' && ft_strchr(token->data, '$') && token->type != EXIT_STATUS)
			{
				var_name = ft_strdup(token->data); //no leaks
				free(token->data);
				token->data = var_name;
				expanded = expand_variable(token->data, envp);
				free(token->data);
				token->data = expanded;
			}
		}
			if (token)
				token = token->next;
	}
}







// norminette
// int	is_alnum(char c)
// {
// 	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
// }
// int	is_digit(char c)
// {
// 	return (c >= '1' && c <= '9');
// }
// void	print_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 		printf("%s\n", envp[i++]);
// }

// //libft_tools
// char	*ft_strndup(const char *s1, size_t n)
// {
// 	size_t	i;
// 	char	*dup;

// 	dup = malloc(n + 1);
// 	i = 0;
// 	if (!dup)
// 		return (NULL);
// 	while (i < n)
// 	{
// 		dup[i] = s1[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while ((s1[i] || s2[i]) && i < n)
// 	{
// 		if (s1[i] == s2[i])
// 			i++;
// 		else
// 			return  ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	}
// 	return (0);
// }
// //expand $0 $5678 $-
// char *allocate_for_special_exp(char *data)
// {
// 	char *temp_data;
// 	char *new;

// 	temp_data = strchr(data, '$');
// 	if (temp_data && *(temp_data + 1) == '0')
// 		new = malloc(strlen(data) + 4); // Extra space for "bash"
// 	else if (temp_data && is_digit(*(temp_data + 1)))
// 		new = malloc(strlen(data)); // Skip one character for the digit
// 	else if (temp_data && *(temp_data + 1) == '-')
// 		new = malloc(strlen(data) + 5); // Extra space for "himBH"
// 	else
// 		new = ft_strdup(data);
// 	if (!new)
// 		return (NULL);
// 	return new;
// }
// int	handle_zero(char **data, char **new_ptr)
// {
// 	if (**data == '$' && *(*data + 1) == '0')
// 	{
// 		strcpy(*new_ptr, "bash");
// 		(*new_ptr) += 4;
// 		*data += 2;
// 		return (1);
// 	}
// 	return (0);
// }
// char *handle_digit_after_dollar_sign(char *data)
// {
// 	char *new;
// 	char *new_ptr;

// 	new = allocate_for_special_exp(data);
// 	if (!new || !data)
// 		return NULL;
// 	new_ptr = new;
// 	while (*data)
// 	{
// 		if (handle_zero(&data, &new_ptr))
// 			continue; //we skip here the rest of the loop if it's handled by handle_zero
// 		if (*data == '$' && *(data + 1) == '-')
// 		{
// 			strcpy(new_ptr, "himBH");
// 			new_ptr += 5;
// 			data += 2;
// 		}
// 		else if (*data == '$' && is_digit(*(data + 1)))
// 			data += 2;
// 		else
// 			*new_ptr++ = *data++;
// 	}
// 	*new_ptr = '\0';

// 	return (new);
// }

// //handle this :
// //// $*
// //$^
// //$$USER ASK ABOUT THIS
// //$USER"'"
// //$-HHH
// //$? Should stay the same 'exit status'

// typedef struct s_data
// {
// 	//expanding_var
// 	int		i;
// 	int		var_len;
// 	char	*start;
// 	char	*var;
// 	size_t	exp_len;
// 	char	*exp;
// 	char	*ptr;
// 	char	*value;
// 	char	*name;
// 	int		is_home;
// 	char	*data;

// }			t_data;

// static void	process_variable_expansion(char **data, t_data *mydata, char **envp)
// {
// 	mydata->start = *data;
// 	while (**data && **data != ' ' && **data != '$' && isalnum(**data))
// 		(*data)++;
// 	mydata->var_len = *data - mydata->start;
// 	mydata->var = ft_strndup(mydata->start, mydata->var_len);
// 	mydata->i = 0;
// 	while (envp[mydata->i])
// 	{
// 		if (ft_strncmp(envp[mydata->i], mydata->var, mydata->var_len) == 0 && envp[mydata->i][mydata->var_len] == '=')
// 		{
// 			mydata->exp_len += ft_strlen(envp[mydata->i] + mydata->var_len + 1); // Skip the name of the variable
// 			break;
// 		}
// 		mydata->i++;
// 	}
// 	free(mydata->var);
// }
// static size_t	expanded_len(char *data, char **envp)
// {
// 	t_data	mydata;

// 	mydata.exp_len = 0;
// 	while (*data)
// 	{
// 		if (*data == '$')
// 		{
// 			data++;
// 			process_variable_expansion(&data, &mydata, envp);
// 		}
// 		else
// 		{
// 			mydata.exp_len++;
// 			data++;
// 		}
// 	}
// 	return (mydata.exp_len);
// }


// static char	*get_variable_value(t_data *mydata, char **envp)
// {
// 	// int flag = 0;
// 	mydata->value = ft_strdup("");
// 	if (mydata->is_home)
// 		mydata->value = getenv("HOME");
// 	else
// 	{
// 		mydata->i = 0;
// 		while (envp[mydata->i])
// 		{
// 			if (strncmp(envp[mydata->i], mydata->var, mydata->var_len) == 0 &&
// 				envp[mydata->i][mydata->var_len] == '=')
// 			{
// 				mydata->value = envp[mydata->i] + mydata->var_len + 1;
// 				// flag = 1;
// 				break;
// 			}
// 			mydata->i++;
// 		}
// 		// if(flag == 0)
// 			// mydata->value = ft_strdup("");
// 	}
// 	return (mydata->value);
// }
// static void handle_special_characters(char **data, char **envp, t_data *mydata)
// {
// 	if (**data == '~')
// 	{
// 		mydata->is_home = 1;
// 		(*data)++;
// 		mydata->var_len = 0;
// 		mydata->var = NULL;
// 		mydata->value = get_variable_value(mydata, envp);
// 		strcpy(mydata->ptr, mydata->value);
// 		mydata->ptr += ft_strlen(mydata->value);
// 	}
// 	else if (**data == '$')
// 	{
// 		(*data)++;
// 		mydata->start = *data;
// 		while (**data && **data != ' ' && **data != '$' &&
// 				**data != '~' && is_alnum(**data))
// 			(*data)++;
// 		mydata->var_len = *data - mydata->start;
// 		mydata->var = ft_strndup(mydata->start, mydata->var_len);
// 		mydata->is_home = 0;
// 		mydata->value = get_variable_value(mydata, envp);
// 		strcpy(mydata->ptr, mydata->value);
// 		mydata->ptr += ft_strlen(mydata->value);
// 		free(mydata->var);
// 	}
// }
// char	*protect_malloc(t_data *mydata)
// {
// 	if (!mydata)
// 		return (NULL);
// 	return (NULL);
// }
// char *expand_variable(char *data, char **envp)
// {
// 	t_data	*mydata;

// 	mydata= (t_data *)malloc(sizeof(t_data));
// 	protect_malloc(mydata);
// 	mydata->is_home = 0;
// 	if (*data == '~')
// 		mydata->exp_len = ft_strlen(getenv("HOME")) + ft_strlen(data + 1);
// 	else
// 		mydata->exp_len = expanded_len(data, envp);
// 	mydata->exp = malloc(mydata->exp_len + 1);
// 	if (!mydata->exp)
// 	{
// 		free(mydata);
// 		return NULL;
// 	}
// 	mydata->ptr = mydata->exp;
// 	while (*data)
// 	{
// 		if (*data == '$'  || *data == '~')
// 			handle_special_characters(&data, envp, mydata);
// 		else
// 			*mydata->ptr++ = *data++;
// 	}
// 	*mydata->ptr = '\0';
// 	free(mydata);
// 	return (mydata->exp);
// }


// void	handle_ds(t_token **token, char **envp)
// {
// 	char	*expanded;
// 	if (((*token)->data[0] == '~' && (*token)->data[1] == '/') || ((*token)->data[0] == '~' && (*token)->data[1] == '\0')) //good
// 	{
// 		expanded = expand_variable((*token)->data, envp);
// 		free((*token)->data);
// 		(*token)->data = expanded;
// 	}
// 	else if ((ft_strcmp((*token)->data,"$*") == 0 || ft_strcmp((*token)->data, "\"$*\"") == 0 || ft_strcmp((*token)->data, "$!") == 0 || ft_strcmp((*token)->data, "\"$!\"") == 0) && (*token)->data[0] != '\'')
// 		{
// 			free((*token)->data);
// 			(*token)->data = strdup("\n");
// 		}
// 	else if ((*token)->type == EXIT_STATUS || (*token)->type == DS || ft_strcmp((*token)->data, "$^") == 0 || ft_strcmp((*token)->data, "\"$^\"") == 0)
// 		{
// 			printf("%s", (*token)->data);
// 			(*token) = (*token)->next;
// 		}
// 	else if ((*token)->data[0] != '"' && ft_strchr((*token)->data, '$') && (*token)->data[0] != '\'')
// 	{
// 		expanded = expand_variable((*token)->data, envp);
// 		free((*token)->data);
// 		(*token)->data = expanded;
// 	}
// }
// void	handle_dollar(t_token *token, char **envp)
// {
// 	// char	*var_name;
// 	// char	*expanded;
// 	(void)envp;
// 	// if (!(token->next) && ft_strcmp(token->data, "*") == 0)
// 	// {
// 	// 	token->data = ft_strdup("Makefile");
// 	// 	return ;
// 	// } bulshit
// 	while (token && token->data)
// 	{
// 		if (token->data[0] != '\'')
// 			token->data = handle_digit_after_dollar_sign(token->data);
// 			printf("dataaaa : %p\n", token->data);
// 		if ((token->data[0] == '~' && token->data[1] == '/') || (token->data[0] == '~' && token->data[1] == '\0'))
// 		{
// 			expanded = expand_variable(token->data, envp);
// 			free(token->data);
// 			token->data = expanded;
// 		}
// 		else if ((ft_strcmp(token->data,"$*") == 0 || ft_strcmp(token->data, "\"$*\"") == 0 || ft_strcmp(token->data, "$!") == 0 || ft_strcmp(token->data, "\"$!\"") == 0) && token->data[0] != '\'')
// 		{
// 			free(token->data);
// 			token->data = strdup("\n");
// 		}
// 		// token->type == EXIT_STATUS
// 		else if (token->type == DS || ft_strcmp(token->data, "$^") == 0 || ft_strcmp(token->data, "\"$^\"") == 0)
// 		{
// 			printf("%s", token->data);
// 			token = token->next;
// 		}
// 		else if (token->data[0] != '"' && ft_strchr(token->data, '$') && token->data[0] != '\'')
// 		{
// 			expanded = expand_variable(token->data, envp);
// 			free(token->data);
// 			token->data = expanded;
// 		}
// 		// handle_ds(&token, envp); //good
// 		else if (token->data[0] == '"' && ft_strchr(token->data, '$'))
// 		{
// 			printf("hey\n");
// 			var_name = ft_strdup(token->data);
// 			free(token->data);
// 			token->data = var_name;
// 			expanded = expand_variable(token->data, envp);
// 			free(token->data);
// 			token->data = expanded;
// 		}
// 		else if (token->data[0] == '\'' && ft_strchr(token->data, '$')) //good
// 		{
// 			var_name = ft_strdup(token->data);
// 			free(token->data);
// 			token->data = var_name;
// 		}
// 		printf("token = %p\n", token->data);
// 		if (token)
// 			token = token->next;
// 	}
// }















//to handle
//echo $""


//heredoc + exp
// if (flag && ft_strchr(line, '$'))
// 			line = expand_variable(line, envp);
	// int	flag = 1;
	// if (ft_strchr((char *)limiter, '\'') || ft_strchr((char *)limiter, '"'))
	// 	flag = 0;
