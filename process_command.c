/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:10:16 by chourri           #+#    #+#             */
/*   Updated: 2024/10/10 18:49:58 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_cmd(t_token **lst, char **envp, t_token **new, t_command **cmd)
{
	ft_expand(*lst, envp);
	*new = build_new_tokens_pipe(*lst);
	*cmd = build_cmd(*new);
}

static void	build_tokens_and_flag(t_token **lst, char *output)
{
	*lst = build_token_list(output);
	(*lst)->flag = 0;
}

static void	initialize_it(char **output, t_token **new, t_command **cmd)
{
	*output = NULL;
	*new = NULL;
	*cmd = NULL;
}

static void	free_errors(t_token *lst, char *output)
{
	if (lst)
		free_token_list(lst);
	if (output)
		free(output);
}

char	**process_command(char *input, char **envp)
{
	char		*output;
	t_token		*new_lst;
	t_token		*lst;
	t_command	*cmd;

	initialize_it(&output, &new_lst, &cmd);
	add_npc_to_cmd(input, &output);
	if (output)
	{
		build_tokens_and_flag(&lst, output);
		if (lst)
		{
			if (parse_quotes(input) || parsing(lst))
				return (free_errors(lst, output), envp);
			exp_cmd(&lst, envp, &new_lst, &cmd);
			if (her(cmd, envp))
				return (free_all(&lst, &new_lst, &cmd, 0), free(output), envp);
			remove_quotes_end(cmd);
			envp = execute_cmd(cmd, envp);
			free_all(&lst, &new_lst, &cmd, 1);
		}
		free(output);
	}
	return (envp);
}
