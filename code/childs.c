/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:00:38 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/19 10:48:05 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *rute, t_pipex *pipex)
{
	pipex->fd_file_in = open(rute, O_RDONLY);
	if (pipex->fd_file_in == -1)
		return (1);
	return (0);
}

int	create_file(char *rute, t_pipex *pipex)
{
	pipex->fd_file_out = open(rute, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_file_out == -1)
		return (1);
	return (0);
}

void	exit_child(t_pipex *pipex)
{
	perror("error");
	close(pipex->tubes[0]);
	close(pipex->tubes[1]);
	close(pipex->fd_file_in);
	close(pipex->fd_file_out);
	exit(1);
}

void	do_first_child(t_pipex *pipex, char *arg, char *infile)
{
	if (open_file(infile, pipex) == 1)
		exit_child(pipex);
	if (get_vals(arg, pipex) == 1)
		exit_child(pipex);
	dup2(pipex->tubes[1], 1);
	dup2(pipex->fd_file_in, 0);
	close(pipex->tubes[0]);
	close(pipex->tubes[1]);
	close(pipex->fd_file_in);
	execve(pipex->path, pipex->cmd, pipex->envp);
	exit_child(pipex);
}

void	do_second_child(t_pipex *pipex, char *arg, char *outfile)
{
	if (create_file(outfile, pipex) == 1)
		exit_child(pipex);
	if (get_vals(arg, pipex) == 1)
		exit_child(pipex);
	dup2(pipex->tubes[0], 0);
	dup2(pipex->fd_file_out, 1);
	close(pipex->tubes[0]);
	close(pipex->tubes[1]);
	close(pipex->fd_file_out);
	execve(pipex->path, pipex->cmd, pipex->envp);
	exit_child(pipex);
}
