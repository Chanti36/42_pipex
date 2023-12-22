/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:33:08 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/18 12:19:56 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h> 
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		tubes[2];
	int		fd_file_in;
	int		fd_file_out;
	char	*path;
	char	**cmd;
	char	**envp;
}	t_pipex;

//rutes
int		get_vals(char *cmd, t_pipex *pipex);
char	**get_paths(t_pipex *pipex);

//forks
void	do_first_child(t_pipex *pipex, char *arg, char *infile);
void	do_second_child(t_pipex *pipex, char *arg, char *outfile);

#endif