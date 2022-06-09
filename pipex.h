/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:41:06 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 00:24:35 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>
# include <errno.h>

size_t	ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*put_path(char *cmd, char *const env[]);
char	*test_access(char *cmd, char *path_line);
char	**ft_split(char *s, char c);
void	free_rest(char **path, int i);
size_t	my_wcnt(const char *s, char c);
size_t	my_wlen(const char *s, char c, size_t i);
void	error_msg(char *err);

#endif