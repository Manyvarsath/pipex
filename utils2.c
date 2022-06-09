/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 03:50:22 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 00:24:50 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**my_freeall(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**my_fillstr(char **split, char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (j < my_wcnt((char *)s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		split[j] = (char *)malloc(sizeof(char)
				* (my_wlen((char *)s, c, i) + 1));
		if (!split)
			return (my_freeall(split));
		while (s[i] != c && s[i])
			split[j][k++] = s[i++];
		split[j][k] = '\0';
		j++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof (char *) * (my_wcnt((char *)s, c) + 1));
	if (!split)
		return (NULL);
	return (my_fillstr(split, s, c));
}

void	free_rest(char **path, int i)
{
	i++;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}
