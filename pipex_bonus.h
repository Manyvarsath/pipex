/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:13:27 by bkamal            #+#    #+#             */
/*   Updated: 2022/06/09 01:32:46 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define BUFFER_SIZE 42

typedef struct s_pipex
{
	char	**cmd;
	int		**pfd;
	int		*pid;
	int		n_args;
	int		n_cmds;
	int		n_pipes;
	int		n_childs;
	int		i;
}	t_pipex;

void	mode_pipex(int ac, char **av, char *const env[]);
void	mode_heredoc(char **av, char *const env[]);
void	close_fd(t_pipex *prm);
void	open_pipes(t_pipex *prm);
void	error_msg(char *err);
void	free_rest(char **path, int i);
void	error_msg(char *err);
char	**ft_split(char *s, char c);
char	*get_next_line(int fd);
char	*put_path(char *cmd, char *const env[]);
char	*test_access(char *cmd, char *path_line);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_nl(char *s1, char *s2);
int		**free_pfd(t_pipex *prm);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(char *s);
size_t	my_wcnt(const char *s, char c);
size_t	my_wlen(const char *s, char c, size_t i);
size_t	ft_strlen_n(const char *s);
size_t	ft_strlen_nl(const char *s);

#endif