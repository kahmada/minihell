/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:10:16 by chourri           #+#    #+#             */
/*   Updated: 2024/10/08 17:13:38 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_token **lst, t_token **new, t_command **cmd, int flg)
{
	free_token_list(*lst);
	free_token_list(*new);
	free_command_list(*cmd);
	if (flg)
		lst = NULL;
}

void	exp_cmd(t_token **lst, char **envp, t_token **new_lst, t_command **cmd)
{
	ft_expand(*lst, envp);
	*new_lst = build_new_tokens_pipe(*lst);
	*cmd = build_cmd(*new_lst);
}

void	build_tokens_and_flag(t_token **lst, char *output)
{
	*lst = build_token_list(output);
	(*lst)->flag = 0;
}

char	**initialize_it(char **output, t_token **new, char *input, char **envp)
{
	*output = NULL;
	*new = NULL;
	if (parse_quotes(input))
		return (envp);
	return (envp);
}

char	**process_command(char *input, char **envp)
{
	char		*output;
	t_token		*new_lst;
	t_token		*lst;
	t_command	*cmd;

	cmd = NULL;
	envp = initialize_it(&output, &new_lst, input, envp);
	add_npc_to_cmd(input, &output);
	if (output)
	{
		build_tokens_and_flag(&lst, output);
		if (lst)
		{
			if (parsing(lst))
				return (free_token_list(lst), free(output), envp);
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
