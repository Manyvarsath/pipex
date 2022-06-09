/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:48:45 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 01:27:37 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_doc(int ac, char *av)
{
	if (ft_strncmp(av, "here_doc", 8) == 0 && ac == 6)
		return (1);
	else if (ft_strncmp(av, "here_doc", 8) != 0 && ac >= 5)
		return (2);
	return (0);
}

void	close_fd(t_pipex *prm)
{
	prm->i = -1;
	while (++prm->i < prm->n_pipes)
	{
		close(prm->pfd[prm->i][0]);
		close(prm->pfd[prm->i][1]);
	}
}

void	open_pipes(t_pipex *prm)
{
	prm->i = -1;
	while (++prm->i < prm->n_pipes)
	{
		if (pipe(prm->pfd[prm->i]) < 0)
			error_msg("Pipe");
	}
}

int	main(int ac, char **av, char *const env[])
{
	if (check_doc(ac, av[1]) == 1)
		mode_heredoc(av, env);
	else if (check_doc(ac, av[1]) == 2)
		mode_pipex(ac, av, env);
	return (0);
}
