/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:55:26 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/19 12:05:05 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_child(t_pipex *pipex)
{
	perror("error");
	close(pipex->new_tubes[0]);
	close(pipex->new_tubes[1]);
	close(pipex->old_tubes[0]);
	close(pipex->old_tubes[1]);
	close(pipex->fd_file_in);
	close(pipex->fd_file_out);
	exit(1);
}

void	do_first_child(t_pipex *pipex)
{
	if (pipex->here_doc == 0)
		if (open_file(pipex->argv[1], pipex) == 1)
			exit_child(pipex);
	if (get_vals(pipex->argv[pipex->arg_i], pipex) == 1)
		exit_child(pipex);
	dup2(pipex->fd_file_in, 0);
	dup2(pipex->new_tubes[1], 1);
	close(pipex->new_tubes[0]);
	close(pipex->new_tubes[1]);
	close(pipex->fd_file_in);
	execve(pipex->path, pipex->cmd, pipex->envp);
	exit_child(pipex);
}

void	do_middle_child(t_pipex *pipex, char *arg)
{
	if (get_vals(arg, pipex) == 1)
		exit_child(pipex);
	dup2(pipex->old_tubes[0], 0);
	dup2(pipex->new_tubes[1], 1);
	close(pipex->new_tubes[0]);
	close(pipex->new_tubes[1]);
	close(pipex->old_tubes[0]);
	close(pipex->old_tubes[1]);
	execve(pipex->path, pipex->cmd, pipex->envp);
	exit_child(pipex);
}

void	do_last_child(t_pipex *pipex)
{
	if (create_file(pipex->argv[pipex->argc - 1], pipex) == 1)
		exit_child(pipex);
	if (get_vals(pipex->argv[pipex->argc - 2], pipex) == 1)
		exit_child(pipex);
	dup2(pipex->new_tubes[0], 0);
	dup2(pipex->fd_file_out, 1);
	close(pipex->new_tubes[0]);
	close(pipex->new_tubes[1]);
	close(pipex->fd_file_out);
	execve(pipex->path, pipex->cmd, pipex->envp);
	exit_child(pipex);
}
