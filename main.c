/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:02:24 by chourri           #+#    #+#             */
/*   Updated: 2024/09/10 19:21:20 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(void)
{
	write(2, "ERROR\n", 6);
	exit(1);
}

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
	// if (s1)
	// 	free((char *)s1);
	return (new_s);
}

int	is_redirection_symbol(int type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_IN
	|| type == REDIRECT_OUT || type == PIPE || type == HEREDOC);
}
int	is_word(int type)
{
	return (type == WORD || type == INSIDE_DOUBLE_QUOTE || type == INSIDE_SINGLE_QUOTE);
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

char *join_token_data(char *combined_data, char *data, int flag)
{
	char *temp;

	if (combined_data)
	{
		if (flag)
			temp = ft_strjoin_space(combined_data, data);
		else
			temp = ft_strjoin(combined_data, data);
		free(combined_data);
	}
	else
		temp = ft_strdup(data);
	return (temp);
}

void	ft_join(char **combined_data, char *data)
{
	(*combined_data) = join_token_data((*combined_data), " ", 1);
	(*combined_data) = join_token_data((*combined_data), data, 1);
	(*combined_data) = join_token_data((*combined_data), " ", 1);
}
t_token *build_new_tokens_pipe(t_token *token)
{
	t_token *new = NULL;
	char *combined_data = NULL;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (is_redirection_symbol(token->type))
			{
				ft_join(&combined_data, token->data);
				// combined_data = join_token_data(combined_data, " ", 1);
				// combined_data = join_token_data(combined_data, token->data, 1);
				// combined_data = join_token_data(combined_data, " ", 1);
			}
			else
				combined_data = join_token_data(combined_data, token->data, 0);
			if (!combined_data)
				return (free_list(new));
			token = token->next;
		}
		if (combined_data)
		{
			ft_lstadd_back_new(&new, WORD, combined_data);
			free(combined_data);
			combined_data = NULL;
		}
		if (token)
			token = token->next;
	}
	return (new);
}

t_command	*build_cmd(t_token *new_token)
{
	t_command	*cmd = NULL;
	t_command	*head = NULL;
	t_command	*prev = NULL;

	while (new_token)
	{
		cmd = (t_command *)malloc(sizeof(t_command));
		if (!cmd)
			return (NULL);
		if (strchr(new_token->data, '"') || strchr(new_token->data, '\''))
			cmd->args = ft_split_cmd_quote(new_token->data);
		else
			cmd->args = ft_split_cmd(new_token->data);
		if (!cmd->args)
			return (NULL);
		cmd->next = NULL;
		if (!head)
			head = cmd;
		if (prev)
			prev->next = cmd;
		prev = cmd;
		new_token = new_token->next;
	}
	return (head);
}

#include <stdlib.h>

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

void print_command(t_command *cmd)
{
	int i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("{%s} ->", cmd->args[i]);
			//printf("%d\n",cmd->fd_in);
			i++;
		}
		printf("NULL\n\n");
		cmd = cmd->next;
	}
}


void remove_quotes(char **args)
{
	int i = 0;
	int j, k;
	char *new_arg;
	char quote_char;
	int in_quotes;

	while (args[i])
	{
		j = 0;
		k = 0;
		in_quotes = 0; // '"'"'$USER'"'"'
		new_arg = (char *)malloc(strlen(args[i]) + 1);
		if (!new_arg)
			return;
		while (args[i][j])
		{
			if (!in_quotes && (args[i][j] == '\'' || args[i][j] == '\"')) // && !is_alphabet(args[i][j + 1])
			{
				in_quotes = 1;
				quote_char = args[i][j];
			}
			else if (in_quotes && args[i][j] == quote_char )
				in_quotes = 0;
			else
				new_arg[k++] = args[i][j];
			j++;
		}
		new_arg[k] = '\0';
		free(args[i]);
		args[i] = new_arg;
		i++;
	}
}

void remove_quotes_END(t_command *cmd)
{
	while (cmd)
	{
		remove_quotes(cmd->args);
		cmd = cmd->next;
	}
}


char **process_command(char *input, char **envp)
{
	char *output = NULL;
	t_token *new_lst = NULL;
	t_token *lst;

	if (parse_quotes(input))
		return (envp);
	(void)lst;

		//test this :  $USER>>DGDFG<< FDGDF
		add_npc_to_cmd(input, &output); //no leaks
		// printf("%s", output);
		if (output)
		{
			lst = build_token_list(output); //no leaks
			// print_list(lst);
			// printf("\n---------------------------------------------------------------\n");
			if (lst)
			{
				// parse_quotes(input);
				//parse syntax error no leaks
				if(parsing(lst))
				{
					// printf("EXIT STATUS : %p\n", manage_exit_status(0, 0));
					// printf("lst : %p\n", lst);
					// printf("output : %p\n", output);
					// free(manage_exit_status(0,0))
					return (free_token_list(lst),free(output), envp);
				}
				// printf("\n\n-------------------------------------BEFORE-----------------------------------------\n\n");
				ft_expand(lst, envp); //no leaks
				// print_list(lst);
				// printf("\n\n-------------------------------------AFTER-----------------------------------------\n\n");
				new_lst = build_new_tokens_pipe(lst); //leaks here
				// printf(" new_lst ==> %p\n", new_lst);
				// printf(" lst ==> %p\n", lst);
				// print_list(new_lst);
				// print_list(new_lst);
				// print_list(new_lst);
				t_command *cmd = build_cmd(new_lst);
				if(her(cmd, envp))
					return(envp);
				remove_quotes_END(cmd);
				// print_command(cmd); //no leaks until here
				// printf("-----COMMAND LINKED LIST-----\n\n");
				envp = execute_cmd(cmd, envp);
				free_token_list(lst);
				free_token_list(new_lst);
				free_command_list(cmd);
				lst = NULL;
			}
			free(output);
		}
			// free(manage_exit_status(0,0));
	return envp;
}



char **process_input(char *input, char **envp)
{
	int stdin_in;
	int stdout_out;
	// signal(SIGINT, handle_signals);
	// signal(SIGINT, SIGINT_handler);
	if (strlen(input) > 0)
	{
		add_history(input);
		stdin_in = dup(0);
		stdout_out = dup(1);
		envp = process_command(input, envp);
		signal(SIGINT, SIGINT_handler); //added
		dup2(stdout_out,1);
		dup2(stdin_in,0);
		close(stdin_in);
		close(stdout_out);
	}
	return(envp);
}
char **ft_envp_copy(char **envp)
{
	int i;
	char **envp_copy;

	i = 0;
	while (envp[i])
		i++;
	envp_copy = (char **)malloc((i + 1) * sizeof(char *));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

int main(int ac, char **av, char **envp)
{
	char *input;
	char **envp_copy;
	rl_catch_signals = 0; //to not print ^C in the prompt
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIGINT_handler);
	envp_copy = ft_envp_copy(envp);
	(void)ac;
	(void)av;
	input = readline("minihell$ ");
	while (input)
	{
		if (!input)
		{
			// char *ex = manage_exit_status(0,1);
			// free(ex);
			break;
		}
		envp_copy = process_input(input, envp_copy); // when I remove it : no leaks but no changes to the env when I export sth
		free(input);
		input = readline("minihell$ ");
	}
	free(envp_copy);
	return (write(2, "exit\n", 5), 0);
}


// int main(int ac, char **av, char **envp)
// {
// 	char *input;
// 	char **envp_copy;

// 	rl_catch_signals = 0; //to not print ^C in the prompt
// 	signal(SIGQUIT, SIG_IGN);
// 	envp_copy = ft_envp_copy(envp);
// 	(void)ac;
// 	(void)av;
// 	while (1)
// 	{
// 		signal(SIGINT, SIGINT_handler);
// 		input = readline("minihell$ ");
// 		// if (sig_received == SIGINT)
// 		// {
// 		// 	sig_received = 0;
// 		// 	free(input);
// 		// 	continue;
// 		// }
// 		//here we handle EOF "Ctrl+"
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		envp_copy = process_input(input, envp_copy);
// 	}
// 	return (0);
// }















//verwendet utiliser
//er wird verwendet zu das aktualle prossez durch eines neues prossez zu ersetzen
//jedoch dieselbe. cependant pareil.
//salam khadija bikhir kulshi mezyan?? lah 7fdak shno coucou !!
