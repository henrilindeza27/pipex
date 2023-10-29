/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:20:45 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/25 15:20:50 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

char	*get_cmdpath(char *cmd, char **env);
void	free_arr(char **arr);
void	child(char **argv, char **env, int *fd_arr);
void	father(char **argv, char **env, int *fd_arr);
void	exec(char *cmd, char **env);

#endif