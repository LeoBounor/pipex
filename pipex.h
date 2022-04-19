/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:55:16 by lbounor           #+#    #+#             */
/*   Updated: 2022/04/19 16:10:02 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_command
{
	char	*pathname;
	char	**argv;
	int		pid;
}	t_command;

typedef struct s_pipex
{
	char				*infile;
	char				*outfile;
	char				**paths;
	int					pipe[2];
	struct s_command	cmd[2];
}	t_pipex;

void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strchr(const char *str, int c);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char *str);

#endif