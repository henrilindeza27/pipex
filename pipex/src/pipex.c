/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:45:24 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/26 13:14:44 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (argc < 5)
		return (-1);
	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child(argv, env, fd);
	father(argv, env, fd);
	return (0);
}
