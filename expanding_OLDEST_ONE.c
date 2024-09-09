/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/09/06 16:13:55 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*new_s;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1 && s2)
// 		return (ft_strdup(s2));
// 	if (!s2 && s1)
// 		return (ft_strdup(s1));
// 	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!new_s)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		new_s[i] = s1[i];
// 		i++ ;
// 	}
// 	j = 0;
// 	while (s2[j])
// 		new_s[i++] = s2[j++];
// 	new_s[i] = '\0';
// 	return (new_s);
// }

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
// static char	*ft_strchr(char *s, int c)
// {
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	return (NULL);
// }

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

// static char *remove_quotes(char *data)
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
// 					exp_len += ft_strlen(envp[i] + var_len + 1); // to skip the name of the variable in the environment cus it is that way written in the environment VAR_NAME = VALUE We want the value
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
// static char *expand_variable(t_token *token, char **envp)
// {
// 	size_t exp_len;
// 	char *exp;
// 	char *data = token->data;
// 	char *ptr;
// 	const char *start;
// 	int var_len;
// 	char *var;
// 	char *value;
// 	int i;

// 	exp_len = expanded_len(data, envp);
// 	exp = malloc(exp_len + 1);
// 	ptr = exp;
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
// 			value = "";
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

char *handle_digit_after_dollar_sign(char *data)
{
	char *new;
	char *temp_data;

	if (!data)
		return NULL;
	temp_data = strchr(data, '$');
	if (temp_data && *(temp_data + 1) == '0' )
	{
		new = malloc(strlen(data) + 4); // Extra space for "bash"
		if (!new)
			return NULL;
	}
	else if (temp_data && isdigit(*(temp_data + 1)))
	{
		new = malloc(strlen(data)); // Skip one character for the digit
		if (!new)
			return NULL;
	}
	else if (temp_data && *(temp_data + 1) == '-')
	{
		new = malloc(strlen(data) + 5);
		if (!new)
			return (NULL);
	}
	else
	{
		new = ft_strdup(data);
		return (new);
	}
	char *new_ptr = new;
	while (*data)
	{
		if (*data == '$' && *(data + 1) == '0')
		{
			strcpy(new_ptr, "bash");
			new_ptr += 4;
			data += 2;
		}
		else if (*data == '$' && *(data + 1) == '-')
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
	free(new_ptr);
	// free(data);
	printf("\nnew_ptr : %p\n", new_ptr);
	printf("\nDATA : %p\n", new_ptr);
	return (new);
}

// void	handle_dollar(t_token *token, char **envp)
// {
// 	char	*var_name;
// 	char	*expanded;

// 	while (token && token->data)
// 	{
// 		if (token->data[0] != '\'')
// 			token->data = handle_digit_after_dollar_sign(token->data);
// 		if (token->type == EXIT_STATUS || token->type == DS || ft_strcmp(token->data, "$^") == 0 || ft_strcmp(token->data, "\"$^\"") == 0)
// 		{
// 			printf("%s", token->data);
// 			token = token->next;
// 		}
// 		else if ((ft_strcmp(token->data,"$*") == 0 || ft_strcmp(token->data, "\"$*\"") == 0 || ft_strcmp(token->data, "$!") == 0 || ft_strcmp(token->data, "\"$!\"") == 0) && token->data[0] != '\'')
// 		{
// 			free(token->data);
// 			token->data = strdup("\n");
// 		}
// 		// else if (token->type == EXIT_STATUS || token->type == DS || ft_strcmp(token->data, "$^") == 0 || ft_strcmp(token->data, "\"$^\"") == 0)
// 		// {
// 		// 	printf("%s", token->data);
// 		// 	token = token->next;
// 		// }
// 		else if (token->data[0] != '"' && ft_strchr(token->data, '$') && token->data[0] != '\'')
// 		{
// 			expanded = expand_variable(token, envp);
// 			free(token->data);
// 			token->data = expanded;
// 		}
// 		else if (token->data[0] == '"' && ft_strchr(token->data, '$'))
// 		{
// 			var_name = ft_strdup(token->data);
// 			free(token->data);
// 			token->data = var_name;
// 			expanded = expand_variable(token, envp);
// 			free(token->data);
// 			token->data = expanded;
// 		}
// 		else if (token->data[0] == '\'' && ft_strchr(token->data, '$'))
// 		{
// 			var_name = ft_strdup(token->data);
// 			free(token->data);
// 			token->data = var_name;
// 		}
// 		if (token && token->data)
// 			printf("%s", token->data);
// 		if (token)
// 			token = token->next;
// 	}
// 	printf("\n");
// }

//handle this :
//// $*
//$^
//$$USER ASK ABOUT THIS
//$USER"'"
//$-HHH
//$? Should stay the same 'exit status'

static size_t	expanded_len(char *data, char **envp)
{
	size_t	exp_len;
	char	*start;
	int		var_len;
	char	*var;
	int		i;

	exp_len = 0;
	while (*data)
	{
		if (*data == '$')
		{
			data++;
			start = data;
			while (*data && *data != ' ' && *data != '$' && is_alnum(*data))
				data++;
			var_len = data - start;
			var = ft_strndup(start, var_len);
			i = 0;
			while (envp[i])
			{
				if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
				{
					exp_len += ft_strlen(envp[i] + var_len + 1); // to skip the name of the variable in the environment cus it is that way written in the environment VAR_NAME = VALUE We want the value
					break ;
				}
				i++;
			}
			free(var);
		}
		else
		{
			exp_len++;
			data++;
		}
	}
	return (exp_len);
}
char *expand_variable(char *data, char **envp)
{
	size_t exp_len;
	char *exp;
	// char *data = token->data;
	char *ptr;
	const char *start;
	int var_len;
	char *var;
	char *value;
	char *name = NULL;
	int i;
	int	is_home = 0;

	if (data[0] == '~')
	{
		char *name = getenv("HOME");
		exp_len = ft_strlen(name) + ft_strlen(data + 1);
		exp = malloc(exp_len + 1);
	}
	else
	{
		exp_len = expanded_len(data, envp);
		exp = malloc(exp_len + 1);
	}
	ptr = exp;
	while (*data)
	{
		if (*data == '$' || *data == '~')
		{
			if (*data == '~')
			{
				is_home = 1;
				name = getenv("HOME");
			}
			data++;
			start = data;
			while (*data && *data != ' ' && *data != '$' && *data != '~' && is_alnum(*data))
				data++;
			var_len = data - start;
			var = ft_strndup(start, var_len);
			i = 0;
			value = "";
			if (is_home)
				value = name;
			while (envp[i])
			{
				if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
				{
					value = envp[i] + var_len + 1;
					break;
				}
				i++;
			}
			strcpy(ptr, value);
			ptr += ft_strlen(value);
			free(var);
		}
		else
			*ptr++ = *data++;
	}
	*ptr = '\0';
	return exp;
}
void	handle_dollar(t_token *token, char **envp)
{
	char	*var_name;
	char	*expanded;

	while (token && token->data)
	{
		if (token->data[0] != '\'')
			token->data = handle_digit_after_dollar_sign(token->data);
		if ((token->data[0] == '~' && token->data[1] == '/') || (token->data[0] == '~' && token->data[1] == '\0'))
		{
			expanded = expand_variable(token->data, envp);
			free(token->data);
			token->data = expanded;
		}
		else if (token->type == EXIT_STATUS || token->type == DS || ft_strcmp(token->data, "$^") == 0 || ft_strcmp(token->data, "\"$^\"") == 0)
		{
			printf("%s", token->data);
			token = token->next;
		}
		else if ((ft_strcmp(token->data,"$*") == 0 || ft_strcmp(token->data, "\"$*\"") == 0 || ft_strcmp(token->data, "$!") == 0 || ft_strcmp(token->data, "\"$!\"") == 0) && token->data[0] != '\'')
		{
			free(token->data);
			token->data = strdup("\n");
		}
		// else if (token->type == EXIT_STATUS || token->type == DS || ft_strcmp(token->data, "$^") == 0 || ft_strcmp(token->data, "\"$^\"") == 0)
		// {
		// 	printf("%s", token->data);
		// 	token = token->next;
		// }
		else if (token->data[0] != '"' && ft_strchr(token->data, '$') && token->data[0] != '\'')
		{
			expanded = expand_variable(token->data, envp);
			free(token->data);
			token->data = expanded;
		}
		else if (token->data[0] == '"' && ft_strchr(token->data, '$'))
		{
			var_name = ft_strdup(token->data);
			free(token->data);
			token->data = var_name;
			expanded = expand_variable(token->data, envp);
			free(token->data);
			token->data = expanded;
		}
		// else if (token->data[0] == '\'' && ft_strchr(token->data, '$'))
		// {
		// 	var_name = ft_strdup(token->data);
		// 	free(token->data);
		// 	token->data = var_name;
		// }
		if (token)
			token = token->next;
	}
}









//norminette
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
// 	{
// 		new = ft_strdup(data);
// 		free(data); //added
// 	}
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
// 	{
// 		free(new);
// 		free(data);
// 		return NULL;
// 	}
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
// 	return new;
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
// 		free(mydata->value); //added
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
// 	printf("Makefile =  %p\n", mydata->data);
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
// 	char *r = ft_strdup(mydata->exp);
// 	// free(mydata->exp);
// 	free(mydata);

// 	return (r);
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
// 		// printf("var_name: %p\n", (*token)->data);
// 	}
// }
// void	handle_dollar(t_token *token, char **envp)
// {
// 	char	*var_name;
// 	char	*expanded;

// 	// if (!(token->next) && ft_strcmp(token->data, "*") == 0)
// 	// {
// 	// 	token->data = ft_strdup("Makefile");
// 	// 	return ;
// 	// } bulshit
// 	while (token && token->data)
// 	{
// 		if (token->data[0] != '\'')
// 		{
// 			token->data = handle_digit_after_dollar_sign(token->data);
// 		}
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
// 			// printf("EXPANDED : %p\n", expanded);
// 			free(token->data);
// 			token->data = expanded;

// 		}
// 		// handle_ds(&token, envp); //good
// 		else if (token->data[0] == '"' && ft_strchr(token->data, '$'))
// 		{
// 			// printf("hey\n");
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
// 		// printf("data : %s\n", token->data);
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
