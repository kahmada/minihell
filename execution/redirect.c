/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:39:02 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/15 16:58:46 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirect_in(char *filename)
{
	int		fd;
	char	*ex;

	if (filename[0] == '$' && filename[1] != '\0')
	{
		ex = manage_exit_status(1, 1);
		printf("%s: ambiguous redirect\n", filename);
		free(ex);
		exit(1);
	}
	ft_remove_quotes(&filename);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	handle_here_doc_redirect(t_command *cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	args = cmd->args;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			dup2(cmd->fd_in, 0);
			close(cmd->fd_in);
			j = i;
			while (args[j + 2] != NULL)
			{
				args[j] = args[j + 2];
				j++;
			}
			args[j] = NULL;
			args[j + 1] = NULL;
			return ;
		}
		i++;
	}
}

void	handle_redirect_out(char *filename)
{
	int		fd;
	char	*ex;

	if (filename[0] == '$' && filename[1] != '\0')
	{
		ex = manage_exit_status(1, 1);
		printf("%s: ambiguous redirect\n", filename);
		free(ex);
		exit(1);
	}
	ft_remove_quotes(&filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redirect_append(char *filename)
{
	int		fd;
	char	*ex;

	if (filename[0] == '$' && filename[1] != '\0')
	{
		ex = manage_exit_status(1, 1);
		printf("%s: ambiguous redirect\n", filename);
		free(ex);
		exit(1);
	}
	ft_remove_quotes(&filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(filename);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
