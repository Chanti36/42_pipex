/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:35:09 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/12/20 10:07:01 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_rutes(char **rutes)
{
	int	i;

	i = 0;
	while (rutes[i])
	{
		free(rutes[i]);
		++i;
	}
	free(rutes);
}

char	**get_paths(t_pipex *pipex)
{
	int		i;
	char	*aux;
	char	**rutes;

	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp(pipex->envp[i], "PATH", 4) == 0)
		{
			aux = ft_substr(pipex->envp[i], 5, ft_strlen(pipex->envp[i]) - 5);
			rutes = ft_split(aux, ':');
			free(aux);
			return (rutes);
		}
		++i;
	}
	return (NULL);
}

int	check_rute(char *rute, t_pipex *pipex)
{
	char	*aux;
	char	*cmd;

	aux = ft_strjoin(rute, "/");
	cmd = ft_strjoin(aux, pipex->cmd[0]);
	free(aux);
	if (access(cmd, X_OK) == 0)
	{
		pipex->path = cmd;
		return (0);
	}
	free(cmd);
	return (1);
}

int	get_vals(char *cmd, t_pipex *pipex)
{
	int		i;
	char	**rutes;

	i = 0;
	pipex->cmd = ft_split(cmd, ' ');
	if (access(pipex->cmd[0], X_OK) == 0)
	{
		pipex->path = pipex->cmd[0];
		return (0);
	}
	rutes = get_paths(pipex);
	if (!rutes)
		return (1);
	while (rutes[i])
	{
		if (check_rute(rutes[i], pipex) == 0)
			return (free_rutes(rutes), 0);
		++i;
	}
	free_rutes(rutes);
	return (1);
}
