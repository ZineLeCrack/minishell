/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:08:28 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/20 14:00:44 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	execute_command(char **envp, char **args)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);
	free(cmd_path);
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	ft_direction(char *input, char **envp, char **args)
{
	char	*cut;

	cut = ft_strchr(input, '<');
	if (input && cut && cut[1] && cut[1] == '<')
		ft_heredoc(input);
	else if (ft_strchr(input, '<'))
		ft_other_redirection(input, envp);
	else if (ft_strchr(input, '>'))
		ft_redirection(input, envp);
	else
		execute_command(envp, args);
}

void	ft_shell(char **envp, char *input)
{
	char	**args;

	args = ft_split_quote(input);
	if (!args || !args[0])
	{
		free(args);
		exit(EXIT_FAILURE);
	}
	ft_direction(input, envp, args);
	free_array(args);
}
