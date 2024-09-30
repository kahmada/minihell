/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:55:39 by kahmada           #+#    #+#             */
/*   Updated: 2024/09/30 16:34:49 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**extract_paths_from_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
	{
		return (NULL);
	}
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

char *check_absolute_path(char *cmd)
{
    DIR *dir = opendir(cmd);

    if (dir)
    {
        fprintf(stderr, "%s: is a directory\n", cmd);
        closedir(dir);
        cmd = "1";
        return (cmd);
    }
    else
    {
        if (access(cmd, F_OK) == 0)
        {
            if (access(cmd, X_OK) == 0)
                return (cmd);
            else
            {
                fprintf(stderr, "%s: no such file or directory\n", cmd);
                cmd = "2";
                return (cmd);
            }
        }
        else
        {
            fprintf(stderr, "%s: no such file or directory\n", cmd);
            cmd = "2";
            return (cmd);
        }
    }
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
		return (cmd);
	else if (cmd[0] == '/')
		return (check_absolute_path(cmd));
	paths = extract_paths_from_envp(envp);
	if (!paths)
	{
		fprintf(stderr, "%s: no such file or directory\n", cmd);
		exit(1);
	}	
	path = find_command_in_paths(cmd, paths);
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (path);
}
