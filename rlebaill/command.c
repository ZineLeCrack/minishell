/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:26:34 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/20 12:36:30 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **split, t_list *env)
{
	if (!split || !env)
		return (1);
	if (!split[1])
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror("Error: \
HOME does not exist in the environment\n"), 1);
		return (0);
	}
	if (split[2])
		return (ft_putstr_fd(" too many arguments\n", 2), 1);
	if (chdir(split[1]) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(split[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	ft_echo(char **split)
{
	int	i;

	i = 1;
	if (!split[i])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (ft_strcmp(split[1], "-n") == 0)
	{
		i++;
		if (!split[i])
			return (0);
	}
	ft_putstr_fd(split[i], 1);
	i++;
	while (split[i])
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(split[i], 1);
		i++;
	}
	if (!(ft_strcmp(split[1], "-n") == 0))
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_shell(char **envp, char **args)
{
	pid_t		pid;
	char		*cmd_path;
	int			i;

	i = 0;
	if (!args)
		return (1);
	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	if (!cmd_path)
		return (perror("Error: malloc error\n"), 1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			ft_putstr_fd(" command not found\n", 2);
			exit(127);
		}
	}
	free(cmd_path);
	waitpid(pid, &i, 0);
	return ((i >> 8) & 0xFF);
}

int	ft_exec(char **split, char **envp)
{
	pid_t	pid;
	int		status;

	if (!split[0][2])
	{
		ft_putstr_fd(" Permission denied: ./\n", 2);
		return (126);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork error\n");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(&split[0][2], split, envp) == -1
			&& ft_have_rights(&split[0][2]))
			exit (127);
		exit(126);
	}
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
