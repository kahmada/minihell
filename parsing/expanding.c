/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:23:50 by chourri           #+#    #+#             */
/*   Updated: 2024/09/13 13:03:39 by chourri          ###   ########.fr       */
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

static size_t expanded_len(char *data, char **envp)
{
	size_t exp_len = 0;
	char *start;
	int var_len;
	char *var;
	int i;
	char	*ex;

	while (*data)
	{
		if (*data == '$' && *(data+ 1) == '?')
		{
			ex = manage_exit_status(0, 0);
			exp_len += ft_strlen(ex);
			free(ex);
			data += 2;
		}
		else if (*data == '$' && is_alnum(*(data + 1)))
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
			else if (is_digit(*data))
				data++;
			else
			{
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
						exp_len += ft_strlen(envp[i] + var_len + 1);
						break;
					}
					i++;
				}
				free(var);
			}
		}
		else
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
	char	*ex;
	exp_len = expanded_len(data, envp);
	exp = malloc(exp_len + 1);
	if (!exp)
		return NULL;

	ptr = exp;
	while (*data)
	{
		if (*data == '$' && *(data+1) == '?')
		{
			ex = manage_exit_status(0, 0);
			strcpy(ptr, ex);
			ptr += ft_strlen(ex);
			free(ex);
			data += 2;
		}
		else if (*data == '$' && is_alnum(*(data + 1)))
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
			else if (is_digit(*data))
				data++;
			else
			{
				start = data;
				while (*data && *data != ' ' && *data != '$' && is_alnum(*data))
					data++;
				var_len = data - start;
				var = ft_strndup(start, var_len);
				i = 0;
				value = "";
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











//to handle
//echo $""
