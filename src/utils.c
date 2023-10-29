/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:46:25 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/25 15:19:54 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*get_pathvalue(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && (env[i][j] != '='))
			j++;
		str = ft_substr(env[i], 0, j);
		if (ft_strncmp(str, "PATH", ft_strlen(str)) == 0)
		{
			free(str);
			return (env[i] + j + 1);
		}
		free(str);
	}
	return (NULL);
}

char	*get_cmdpath(char *cmd, char **env)
{
	int		i;
	char	**path_values;
	char	**cmds;
	char	*actual_path;
	char	*path;

	path_values = ft_split(get_pathvalue(env), ':');
	cmds = ft_split(cmd, ' ');
	i = -1;
	while (path_values[++i])
	{
		actual_path = ft_strjoin(path_values[i], "/");
		path = ft_strjoin(actual_path, cmds[0]);
		free(actual_path);
		if (access(path, X_OK | F_OK) == 0)
		{
			free_arr(path_values);
			free_arr(cmds);
			return (path);
		}
		free(path);
	}
	free_arr(path_values);
	free_arr(cmds);
	return (cmd);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	child(char **argv, char **env, int *fd_arr)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		exit(0);
	dup2(fd, 0);
	dup2(fd_arr[1], 1);
	close(fd_arr[0]);
	exec(argv[2], env);
}

void	father(char **argv, char **env, int *fd_arr)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit(0);
	dup2(fd, 1);
	dup2(fd_arr[0], 0);
	close(fd_arr[1]);
	exec(argv[3], env);
}
