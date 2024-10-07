/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:02:24 by chourri           #+#    #+#             */
/*   Updated: 2024/10/07 15:59:29 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_input(char *input, char **envp)
{
	int	stdin_in;
	int	stdout_out;

	if (strlen(input) > 0)
	{
		add_history(input);
		stdin_in = dup(0);
		stdout_out = dup(1);
		envp = process_command(input, envp);
		signal(SIGINT, sigint_handler);
		dup2(stdout_out, 1);
		dup2(stdin_in, 0);
		close(stdin_in);
		close(stdout_out);
	}
	return (envp);
}

char	**ft_envp_copy(char **envp)
{
	int		i;
	char	**envp_copy;

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

void	fill_empty_envp(char **envp)
{
	if (envp[0] == NULL)
	{
		envp[0] = "PWD=/Users";
		envp[1] = "SHLVL=1";
		envp[2] = "_=/usr/bin/env";
		envp[3] = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
		envp[4] = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*input;
	char			**envp_copy;
	struct termios	termios_p;

	(void)ac;
	(void)av;
	// rl_catch_signals = 0;
	g_sig_received = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	fill_empty_envp(envp);
	envp_copy = ft_envp_copy(envp);
	input = readline("minihell$ ");
	tcgetattr(0, &termios_p);
	while (input)
	{
		if (!input)
			break ;
		envp_copy = process_input(input, envp_copy);
		tcsetattr(0, 0, &termios_p);
		free(input);
		input = readline("minihell$ ");
	}
	free(envp_copy);
	return (write(2, "exit\n", 5), 0);
}
