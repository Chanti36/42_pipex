/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:00:38 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/19 12:05:23 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_fork(t_pipex *pipex, pid_t *child)
{
	*child = fork();
	if (*child == -1)
		return (1);
	if (*child == 0)
	{
		pipex->childs[0] = *child;
		do_first_child(pipex);
	}
	return (0);
}

int	loop_fork(t_pipex *pipex, pid_t *child, char *argv, int *child_index)
{
	pipex->old_tubes[0] = pipex->new_tubes[0];
	pipex->old_tubes[1] = pipex->new_tubes[1];
	if (pipe(&pipex->new_tubes[2]) == -1)
		return (1);
	*child = fork();
	if (*child == -1)
		return (1);
	if (*child == 0)
	{
		pipex->childs[*child_index] = *child;
		do_middle_child(pipex, argv);
	}
	close(pipex->old_tubes[0]);
	close(pipex->old_tubes[1]);
	return (0);
}

int	last_fork(t_pipex *pipex, pid_t *child, int *child_index)
{
	*child = fork();
	if (*child == -1)
		return (1);
	if (*child == 0)
	{
		pipex->childs[*child_index] = *child;
		do_last_child(pipex);
	}
	return (0);
}

int	do_forks(t_pipex *pipex)
{
	pid_t	child;
	int		child_index;

	child_index = 1;
	if (pipe(pipex->new_tubes) == -1)
		return (1);
	if (first_fork(pipex, &child) == 1)
		return (1);
	while (++pipex->arg_i < pipex->argc - 2)
	{
		if (loop_fork(pipex, &child, pipex->argv[pipex->arg_i], \
			&child_index) == 1)
			return (1);
		pipex->childs[child_index] = child;
		++child_index;
	}
	if (last_fork(pipex, &child, &child_index) == 1)
		return (1);
	close(pipex->new_tubes[0]);
	close(pipex->new_tubes[1]);
	pipex->childs[pipex->argc - 3 - pipex->here_doc] = -1;
	return (0);
}
