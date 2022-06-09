/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:12:44 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 02:07:59 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_pipex(int ac, t_pipex *prm)
{
	prm->i = -1;
	prm->n_args = ac;
	prm->n_cmds = ac - 3;
	prm->n_pipes = prm->n_cmds - 1;
	prm->pfd = (int **)malloc(sizeof(int) * (prm->n_pipes));
	while (++prm->i < prm->n_cmds)
		prm->pfd[prm->i] = (int *)malloc(sizeof(int) * 2);
	prm->pid = (int *)malloc(sizeof(int) * prm->n_cmds);
}

static void	in_child(t_pipex *prm, char **av, char *const env[])
{
	char	**cmd;
	int		fd_in;

	cmd = ft_split(av[2], ' ');
	fd_in = open(av[1], O_RDONLY, 0644);
	if (fd_in < 0)
		error_msg("File descriptor");
	dup2(fd_in, STDIN_FILENO);
	dup2(prm->pfd[0][1], STDOUT_FILENO);
	close_fd(prm);
	close(fd_in);
	execve(put_path(cmd[0], env), cmd, env);
}

static void	out_child(t_pipex *prm, char **av, char *const env[])
{
	char	**cmd;
	int		fd_out;

	cmd = ft_split(av[prm->n_args - 2], ' ');
	fd_out = open(av[prm->n_args - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_msg("File descriptor");
	dup2(prm->pfd[prm->n_pipes - 1][0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_fd(prm);
	close(fd_out);
	execve(put_path(cmd[0], env), cmd, env);
}

static void	mid_child(t_pipex *prm, char **av, char *const env[], int index)
{
	char	**cmd;

	cmd = ft_split(av[index + 2], ' ');
	dup2(prm->pfd[index - 1][0], STDIN_FILENO);
	dup2(prm->pfd[index][1], STDOUT_FILENO);
	close_fd(prm);
	execve(put_path(cmd[0], env), cmd, env);
}

void	mode_pipex(int ac, char **av, char *const env[])
{
	t_pipex	prm;

	init_pipex(ac, &prm);
	open_pipes(&prm);
	prm.i = -1;
	while (++prm.i < prm.n_cmds)
	{
		prm.pid[prm.i] = fork();
		if (prm.pid[prm.i] < 0)
			error_msg("Fork");
		else if (prm.pid[prm.i] == 0)
		{
			if (prm.i == 0)
				in_child(&prm, av, env);
			else if (prm.i == prm.n_cmds - 1)
				out_child(&prm, av, env);
			else
				mid_child(&prm, av, env, prm.i);
		}
	}
	close_fd(&prm);
	while (wait(NULL) > 0)
		;
	free(prm.pid);
	prm.pfd = free_pfd(&prm);
}
