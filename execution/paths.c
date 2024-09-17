/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:55:39 by kahmada           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/15 16:53:00 by kahmada          ###   ########.fr       */
=======
/*   Updated: 2024/09/15 16:54:10 by chourri          ###   ########.fr       */
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **extract_paths_from_envp(char **envp)
{
	int i;
	char	**error;

	i = 0;
	error = malloc(sizeof(char *));
	*error = "3";
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
	{
		return (error);
	}
	return (ft_split_lib(envp[i] + 5, ':'));
}

void	wrerror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
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

char *find_commande(char *cmd, char **envp)
{
    char **paths;
    char *path;
    struct stat filestat;

    if (!cmd || !cmd[0])
        return NULL;

    // Check if the command starts with '/'
<<<<<<< HEAD
    if (cmd[0] == '.')
        return (cmd);  
    else if (cmd[0] == '/')
=======
	if (cmd[0] == '.')
		return (cmd);
	else if (cmd[0] == '/')
>>>>>>> 2e4895a5baa2e54579d2c8964c1a02732d564670
    {
        // Check if the file exists and is executable
        if (stat(cmd, &filestat) == 0)
        {
            // Check if it's a directory
            if (S_ISDIR(filestat.st_mode))
            {
                fprintf(stderr, "%s: is a directory\n", cmd);
				cmd = "1";
                return cmd;
            }
            // Check if it's executable
            if (access(cmd, X_OK) == 0)
            {
                return (cmd); // Return a duplicate of the command path
            }
            else
            {
                fprintf(stderr, "%s: no such file or directory\n", cmd);
				cmd = "2";
                return cmd;
            }
        }
        else
        {
            fprintf(stderr, "%s: no such file or directory\n", cmd);
            cmd = "2";
            return cmd;
        }
    }
    paths = extract_paths_from_envp(envp);
    if (!paths)
        return NULL;
    if (ft_strcmp(*paths, "3")==0)
		return ("3");
    path = find_command_in_paths(cmd, paths);
    for (int i = 0; paths[i]; i++)
        free(paths[i]);
    free(paths);
    return path;
}

