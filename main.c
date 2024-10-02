/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:02:24 by chourri           #+#    #+#             */
/*   Updated: 2024/10/02 19:42:55 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sig_received = 0;

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

char **process_command(char *input, char **envp)
{
	char *output = NULL;
	t_token *new_lst = NULL;
	t_token *lst;

	if (parse_quotes(input))
		return (envp);
	(void)lst;

		add_npc_to_cmd(input, &output); //no leaks
		if (output)
		{
			lst = build_token_list(output); //no leaks
			lst->flag = 0;
			if (lst)
			{
				if(parsing(lst))
					return (free_token_list(lst),free(output), envp);
				ft_expand(lst, envp); //no leaks
				// print_list(lst);
				new_lst = build_new_tokens_pipe(lst); //leaks here
				t_command *cmd = build_cmd(new_lst);
				if(her(cmd, envp))
				{
					free_token_list(lst);
					free_token_list(new_lst);
					free_command_list(cmd);
					free(output);
					return(envp);
				}
				remove_quotes_end(cmd);
				envp = execute_cmd(cmd, envp);
				free_token_list(lst);
				free_token_list(new_lst);
				free_command_list(cmd);
				lst = NULL;
			}
			free(output);
		}
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
		signal(SIGINT, sigint_handler); //added
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
	//rl_catch_signals = 0; //to not print ^C in the prompt
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	envp_copy = ft_envp_copy(envp);
	(void)ac;
	(void)av;
	input = readline("minihell$ ");
	struct termios termios_p;
	tcgetattr(0, &termios_p);
	while (input)
	{
		if (!input)
			break;
		envp_copy = process_input(input, envp_copy);
		tcsetattr(0, 0, &termios_p);
		free(input);
		input = readline("minihell$ ");
	}
	free(envp_copy);

	return (write(2, "exit\n", 5), 0);
}
