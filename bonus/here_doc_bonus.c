/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:05:54 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/19 12:27:03 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *rute, t_pipex *pipex)
{
	pipex->fd_file_in = open(rute, O_RDONLY);
	if (pipex->fd_file_in == -1)
		return (1);
	return (0);
}

int	create_file(char *rute, t_pipex *pipex)
{
	if (pipex->here_doc == 1)
		pipex->fd_file_out = open(rute, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		pipex->fd_file_out = open(rute, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex->fd_file_out == -1)
		return (1);
	return (0);
}

int	heredoc_manager(char *limitador, t_pipex *pipex)
{
	int		file_aux;
	char	*buff;

	file_aux = open("here_doc", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_aux < 0)
		return (1);
	while (1)
	{
		buff = get_next_line(0);
		if (buff == NULL)
		{
			close(file_aux);
			return (1);
		}
		if (!ft_strncmp(limitador, buff, ft_strlen(limitador)))
			break ;
		write(file_aux, buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
	close(file_aux);
	pipex->fd_file_in = open("here_doc", O_RDONLY);
	if (pipex-> fd_file_in < 0)
		return (1);
	return (0);
}

int	manage_input(t_pipex *pipex)
{
	if (pipex->argc < 5)
		return (1);
	if (ft_strncmp(pipex->argv[1], "here_doc", 8) == 0)
	{
		pipex->here_doc = 1;
		if (heredoc_manager(pipex->argv[2], pipex) == 1)
			return (1);
	}
	else
	{
		pipex->here_doc = 0;
	}
	pipex->arg_i = 2 + pipex->here_doc;
	pipex->childs = (int *)malloc(sizeof(int *) * \
	(pipex->argc - 2 - pipex->here_doc));
	if (pipex->childs == NULL)
		return (1);
	return (0);
}
