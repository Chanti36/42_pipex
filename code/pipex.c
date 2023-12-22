/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:33:01 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/20 10:07:49 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	leaks(void)
{
	system("leaks -q pipex");
}

int	close_parent(t_pipex *pipex, int c1, int c2)
{
	int	status;

	close(pipex->tubes[0]);
	close(pipex->tubes[1]);
	waitpid(c1, NULL, 0);
	waitpid(c2, &status, 0);
	close(pipex->fd_file_in);
	close(pipex->fd_file_out);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	child1;
	pid_t	child2;

	if (argc != 5)
		return (1);
	if (envp != NULL)
		pipex.envp = envp;
	if (pipe(pipex.tubes) == -1)
		exit(1);
	child1 = fork();
	if (child1 == -1)
		exit(1);
	if (child1 == 0)
		do_first_child(&pipex, argv[2], argv[1]);
	child2 = fork();
	if (child2 == -1)
		exit(1);
	if (child2 == 0)
		do_second_child(&pipex, argv[3], argv[4]);
	exit(close_parent(&pipex, child1, child2));
}
