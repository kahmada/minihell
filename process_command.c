/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:10:16 by chourri           #+#    #+#             */
/*   Updated: 2024/10/14 15:09:08 by chourri          ###   ########.fr       */
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

void	initialize_it(char **output, t_token **new, t_command **cmd)
{
	*output = NULL;
	*new = NULL;
	*cmd = NULL;
}

char	**process_command(char *input, char **envp)
{
	t_process_cmd	dt;

	if (parse_quotes(input))
		return (envp);
	initialize_it(&(dt.output), &(dt.new_lst), &(dt.cmd));
	add_npc_to_cmd(input, &(dt.output));
	if (dt.output)
	{
		build_tokens_and_flag(&(dt.lst), (dt.output));
		if (dt.lst)
		{
			if (parsing(dt.lst))
				return (free_token_list(dt.lst), free((dt.output)), envp);
			exp_cmd(&(dt.lst), envp, &(dt.new_lst), &(dt.cmd));
			if (her(dt.cmd, envp))
				return (free_all(&(dt.lst), &(dt.new_lst),
						&(dt.cmd), 0), free((dt.output)), envp);
			remove_quotes_end(dt.cmd);
			envp = execute_cmd(dt.cmd, envp);
			free_all(&(dt.lst), &(dt.new_lst), &(dt.cmd), 1);
		}
		free(dt.output);
	}
	return (envp);
}
