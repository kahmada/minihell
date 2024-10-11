/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:10:16 by chourri           #+#    #+#             */
/*   Updated: 2024/10/11 11:20:06 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


const char*	get_token_type_name(t_type type)
{
	switch (type)
	{
		case COMMAND:
			return "COMMAND";
		case ARGUMENT:
			return "ARGUMENT";
		case PIPE:
			return "PIPE";
		case REDIRECT_IN:
			return "REDIRECT_IN";
		case REDIRECT_OUT:
			return "REDIRECT_OUT";
		case REDIRECT_APPEND:
			return "REDIRECT_APPEND";
		case HEREDOC:
			return "HEREDOC";
		case ENV_VAR:
			return "ENV_VAR";
		case EXIT_STATUS:
			return "EXIT_STATUS";
		case INSIDE_SINGLE_QUOTE:
			return "INSIDE_SINGLE_QUOTE";
		case INSIDE_DOUBLE_QUOTE:
			return "INSIDE_DOUBLE_QUOTE";
		case WORD:
			return "WORD";
		// case END:
		// 	return "END";
		// case ERROR:
		// 	return "ERROR";
		case DS:
			return "DS";
		case SPAACE :
			return "SPACE";
		case TAAB :
			return "TAB";
		default:
			return "UNKNOWN";
	}
}

void	print_list(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current && current->data && current->type)
	{
		printf("Type: %s, Data: {%s}\n",
			get_token_type_name(current->type), current->data);
		current = current->next;
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
		// print_list(lst);
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
