/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:55:05 by lbounor           #+#    #+#             */
/*   Updated: 2022/04/19 16:10:48 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	clear_memory(t_pipex *pipex)
{
	free_split(pipex->paths);
	free(pipex->cmd[0].pathname);
	free_split(pipex->cmd[0].argv);
	free(pipex->cmd[1].pathname);
	free_split(pipex->cmd[1].argv);
}

void	init_command(t_command *command)
{
	command->argv = NULL;
	command->pathname = NULL;
}

char	**find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_split(ft_strchr(env[i], '/'), ':'));
		i++;
	}
	return (NULL);
}

char	*concat(char *split, char *cmd)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(split, "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

t_command	make_cmd(char *cmd, char **split)
{
	int			i;
	char		*tmp;
	t_command	command;

	init_command(&command);
	i = -1;
	while (split[++i])
	{
		tmp = concat(split[i], cmd);
		if (!tmp)
			return (command);
		if (access(tmp, X_OK) == 0)
		{
			command.pathname = tmp;
			command.argv = ft_split(cmd, ' ');
			return (command);
		}
		free(tmp);
	}
	return (command);
}

void	first_cmd(t_pipex *pipex, char *infile)
{
	int	fd_file;

	fd_file = open(infile, O_RDONLY);
	if (fd_file == -1)
		exit(0);
	dup2(fd_file, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	if (!pipex->cmd[0].pathname)
	{
		close(fd_file);
	}
	execve(pipex->cmd[0].pathname, pipex->cmd[0].argv, NULL);
	exit(0);
}

void	last_cmd(t_pipex *pipex, char *infile, char *outfile)
{
	int	fd_file;

	fd_file = open(outfile, O_WRONLY);
	if (fd_file == -1)
		return ;
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(fd_file, STDOUT_FILENO);
	close(pipex->pipe[1]);
	//if (test_input(infile))
	//	close(pipex->pipe[0]);
	if (!pipex->cmd[1].pathname)
		close(pipex->pipe[0]);
	execve(pipex->cmd[1].pathname, pipex->cmd[1].argv, NULL);
	exit(0);
}

void	exec_cmd(t_pipex *pipex, int i)
{
	if (i == 0)
		first_cmd(pipex, pipex->infile);
	else if (i == 1)
		last_cmd(pipex, pipex->infile, pipex->outfile);
}

void	ft_pipex(t_pipex pipex)
{
	int		i;

	i = 0;
	if (pipe (pipex.pipe))
		return ;
	while (i < 2)
	{
		pipex.cmd[i].pid = fork();
		if (pipex.cmd[i].pid < 0)
			return ;
		if (pipex.cmd[i].pid == 0)
			exec_cmd(&pipex, i);
		i++;
	}
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	i = 0;
	while (i < 2)
	{
		waitpid(pipex.cmd[i].pid, NULL, 0);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 5)
	{
		pipex.infile = av[1];
		pipex.outfile = av[4];
		pipex.paths = find_path(env);
		pipex.cmd[0] = make_cmd(av[2], pipex.paths);
		pipex.cmd[1] = make_cmd(av[3], pipex.paths);
		ft_pipex(pipex);
		//printf("%s\n", pipex.cmd1.pathname);
		//printf("%s", pipex.cmd2.pathname);
	}
	else if (ac > 5)
		ft_putendl_fd("Too many arguments!", 1);
	else if (ac < 5)
		ft_putendl_fd("Not enough arguments!", 1);
	clear_memory(&pipex);
	return (0);
}
