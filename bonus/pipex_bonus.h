/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:33:08 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/19 11:53:58 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h> 
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>
# define BUFFER_SIZE 42

typedef struct s_pipex
{
	char	**envp;
	int		argc;
	char	**argv;
	int		new_tubes[2];
	int		old_tubes[2];
	int		fd_file_in;
	int		fd_file_out;
	int		here_doc;
	char	*path;
	char	**cmd;
	int		*childs;
	int		arg_i;
}	t_pipex;

//gnl
char	*get_next_line(int fd);
int		ft_find_line(char *buff);
size_t	ps_strlen(const char *str);
char	*ps_strjoin(char *s1, char const *s2);

//rutes
int		get_vals(char *cmd, t_pipex *pipex);
char	**get_paths(t_pipex *pipex);

//childs
void	do_first_child(t_pipex *pipex);
void	do_middle_child(t_pipex *pipex, char *arg);
void	do_last_child(t_pipex *pipex);

//forks
int		do_forks(t_pipex *pipex);

//heredoc
int		manage_input(t_pipex *pipex);
int		open_file(char *rute, t_pipex *pipex);
int		create_file(char *rute, t_pipex *pipex);

#endif