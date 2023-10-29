/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:45:24 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/29 13:27:44 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	check_here_doc(char **argv, int *fd)
{
	char	*str;

	close(fd[0]);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(str, argv[2], ft_strlen(str)) == 0)
		{
			free(str);
			exit(0);
		}
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
}

void	put_heredoc(char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		check_here_doc(argv, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	if (argc < 5)
		exit(0);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		if (argc < 6)
			exit(0);
		i = 3;
		fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		put_heredoc(argv);
	}
	else
	{
		i = 2;
		fdin = open(argv[1], O_RDONLY, 0777);
		fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fdin, 0);
	}
	while (i < argc - 2)
		make_pipe(argv[i++], env);
	dup2(fdout, 1);
	exec(argv[argc - 2], env);
}
