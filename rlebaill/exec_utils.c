/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:22:35 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/20 18:21:08 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_splited_split(char ***splited_split)
{
	int	i;

	i = 0;
	while (splited_split[i])
	{
		ft_free_split(splited_split[i]);
		i++;
	}
	free(splited_split);
}

int	ft_open_pipe(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "|") == 0)
		{
			if (i == 0)
				return (ft_putstr_fd("minishell: syntax error near \
unexpected token `|\'\n", 2), 1);
			if (!split[i + 1])
				return (ft_putstr_fd("open pipe\n", 2), 1);
		}
		i++;
	}
	return (0);
}

int	ft_have_rights(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	if ((file_stat.st_mode & S_IXUSR)
		|| (file_stat.st_mode & S_IXGRP && getegid() == file_stat.st_gid)
		|| (file_stat.st_mode & S_IXOTH))
		return (ft_putstr_fd(" Is a directory", 2), 0);
	return (ft_putstr_fd(" Permission denied\n", 2), 0);
}

void	ft_fill_pipe(char ***splited_split, int fd[2],
	int prev_fd, t_mini *mini)
{
	int	i;

	i = 0;
	if (splited_split[i + 1])
		dup2(fd[1], STDOUT_FILENO);
	if (prev_fd != 0)
		dup2(prev_fd, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(ft_command(splited_split[i], splited_split, "ok", mini));
}

int	have_double_left(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
