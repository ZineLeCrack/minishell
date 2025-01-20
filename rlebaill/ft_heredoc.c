/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:56 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/20 18:20:14 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_stop_word(char **args, int *index)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			*index = i;
			if (args[i + 1])
				return (ft_strdup(args[i + 1]));
			else
				ft_putstr_fd("Error: No delimiter word\n", 2);
		}
		i++;
	}
	*index = -1;
	return (NULL);
}

static char	**ft_extract_command(char **args, int heredoc_index)
{
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (heredoc_index + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < heredoc_index)
	{
		cmd[i] = ft_strdup(args[i]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

static char	*ft_find_command_path(char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*test_path;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		test_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(test_path, cmd);
		free(test_path);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_split(paths);
	return (NULL);
}

static int	ft_execute_with_heredoc(char **cmd, int pipe_fd[2])
{
	pid_t	pid;
	char	*cmd_path;
	int		i;

	cmd_path = ft_find_command_path(cmd[0]);
	if (!cmd_path)
		return (127);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 127);
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execve(cmd_path, cmd, NULL);
		perror("execve");
		exit(127);
	}
	close(pipe_fd[0]);
	free(cmd_path);
	waitpid(pid, &i, 0);
	return ((i >> 8) & 0xFF);
}

static void	ft_read_and_write_heredoc(char *stop, int pipe_fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (stop && ft_strcmp(line, stop) == 0))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
}

int	ft_heredoc(char **args)
{
	char	*stop;
	int		heredoc_index;
	char	**cmd;
	int		pipe_fd[2];
	int		status;

	status = 0;
	stop = ft_get_stop_word(args, &heredoc_index);
	if (!stop || heredoc_index == -1)
		return (0);
	cmd = ft_extract_command(args, heredoc_index);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 127);
	ft_read_and_write_heredoc(stop, pipe_fd);
	if (cmd[0])
		status = ft_execute_with_heredoc(cmd, pipe_fd);
	ft_free_split(cmd);
	free(stop);
	return (status);
}

// int main()
// {
// 	t_mini mini;
// 	char **args = ft_split_quote("wc -l << test", &mini);

// 	return (ft_heredoc(args));
// }
