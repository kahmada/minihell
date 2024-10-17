/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:55:39 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/17 13:53:56 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**extract_paths_from_envp(char **envp)
{
	int		i;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split_lib(envp[i] + 5, ':'));
}

static char	*find_command_in_paths(char *cmd, char **paths)
{
	char	*path;
	char	*part_ofp;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_ofp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_ofp, cmd);
		free(part_ofp);
		if (access(path, F_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)
		{
			free(path);
			wrerror("permission denied: ");
			wrerror(cmd);
			wrerror("\n");
		}
		i++;
	}
	return (NULL);
}

char	*check_access_rights(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": permission denied\n", 2);
			cmd = "3";
			return (cmd);
		}
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd = "2";
		return (cmd);
	}
}

char	*check_absolute_relativ_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		closedir(dir);
		cmd = "1";
		return (cmd);
	}
	else
		return (check_access_rights(cmd));
}

char	*find_commande(char *cmd, char **envp)
{
	char		**paths;
	char		*path;
	int			i;

	i = 0;
	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '.')
		return (check_absolute_relativ_path(cmd));
	else if (cmd[0] == '/')
		return (check_absolute_relativ_path(cmd));
	paths = extract_paths_from_envp(envp);
	if (!paths)
	{
		if (access(cmd, F_OK) == 0)
			return (check_absolute_relativ_path(cmd));
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	path = find_command_in_paths(cmd, paths);
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (path);
}
