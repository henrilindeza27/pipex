/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:46:25 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/29 13:28:07 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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

void	exec(char *cmd, char **env)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	path = get_cmdpath(cmd, env);
	if (execve(path, cmds, env) == -1)
	{
		perror("command not found");
		exit(0);
	}
}

void	make_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}
