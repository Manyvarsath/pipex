/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:47:22 by bkamal            #+#    #+#             */
/*   Updated: 2022/11/12 01:29:28 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	in_child(char **av, char *const env[], int *pfd)
{
	char	**cmd;
	int		temp_file;

	close(pfd[0]);
	cmd = ft_split(av[3], ' ');
	temp_file = open(".temp_file", O_RDONLY, 0644);
	if (temp_file < 0)
		error_msg("File descriptor");
	dup2(temp_file, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	close(temp_file);
	close(pfd[1]);
	execve(put_path(cmd[0], env), cmd, env);
}

static void	out_child(char **av, char *const env[], int *pfd)
{
	char	**cmd;
	int		out_file;

	close(pfd[1]);
	cmd = ft_split(av[4], ' ');
	out_file = open(av[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_file < 0)
		error_msg("File descriptor");
	dup2(pfd[0], STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
	close(out_file);
	close(pfd[0]);
	execve(put_path(cmd[0], env), cmd, env);
}

static void	heredoc_parent(char **av, char *const env[])
{
	int	pid[2];
	int	pfd[2];

	if (pipe(pfd) < 0)
		error_msg("Pipe");
	pid[0] = fork();
	if (pid[0] == -1)
		error_msg("Fork");
	else if (pid[0] == 0)
		in_child(av, env, pfd);
	pid[1] = fork();
	if (pid[1] == -1)
		error_msg("Fork");
	else if (pid[1] == 0)
		out_child(av, env, pfd);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

void	mode_heredoc(char **av, char *const env[])
{
	char	*temp;
	int		temp_file;

	temp_file = open(".temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_file < 0)
		error_msg("File Descriptor");
	while (1)
	{
		write(1, "> ", 2);
		temp = get_next_line(0);
		if (!ft_strncmp(av[2], temp, ft_strlen(av[2])) && (ft_strlen(temp) == (ft_strlen(av[2]) + 1)))
			break ;
		write(temp_file, temp, ft_strlen(temp));
		free(temp);
	}
	close(temp_file);
	heredoc_parent(av, env);
	unlink(".temp_file");
}
