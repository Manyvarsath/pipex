/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:42:22 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 01:28:04 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_cmd1(char **av, char *const env[], int *pfd)
{
	int		fd1;
	char	**cmd;

	cmd = ft_split(av[2], ' ');
	close(pfd[0]);
	fd1 = open(av[1], O_RDONLY, 0644);
	if (fd1 < 0)
		error_msg("File descriptor");
	dup2(fd1, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	close(fd1);
	close(pfd[1]);
	execve(put_path(cmd[0], env), cmd, env);
}

static void	child_cmd2(char **av, char *const env[], int *pfd)
{
	int		fd0;
	char	**cmd;

	close(pfd[1]);
	cmd = ft_split(av[3], ' ');
	fd0 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd0 < 0)
		error_msg("File descriptor");
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd0, STDOUT_FILENO);
	close(fd0);
	close(pfd[0]);
	execve(put_path(cmd[0], env), cmd, env);
}

static void	pipex(char *av[], char *const env[])
{
	int	pid1;
	int	pid2;
	int	pfd[2];

	if (pipe(pfd) == -1)
		error_msg("Pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_msg("Fork");
	if (pid1 == 0)
		child_cmd1(av, env, pfd);
	pid2 = fork();
	if (pid2 == -1)
		error_msg("Fork");
	if (pid2 == 0)
		child_cmd2(av, env, pfd);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char *const env[])
{
	if (ac != 5)
		return (0);
	pipex(av, env);
	return (0);
}
