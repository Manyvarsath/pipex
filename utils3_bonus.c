/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:41:22 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 01:18:04 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	my_wcnt(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

size_t	my_wlen(const char *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	*test_access(char *cmd, char *path_line)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(path_line, ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], X_OK) == 0)
		{
			free_rest(path, i);
			return (path[i]);
		}
		free(path[i]);
		i++;
	}
	error_msg("Command");
	return (NULL);
}

void	error_msg(char *err)
{
	perror(err);
	exit (1);
}

int	**free_pfd(t_pipex *prm)
{
	prm->i = -1;
	while (++prm->i < prm->n_pipes)
		free(prm->pfd[prm->i]);
	free(prm->pfd);
	return (NULL);
}
