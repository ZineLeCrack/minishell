/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:54:04 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/17 16:11:49 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_list *env)
{
	t_list	*lst;

	lst = env;
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void	ft_is_numeric(char *str, unsigned char *exit_code)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i])
			&& str[i] != '-' && str[i] != '+')
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			*exit_code = 2;
			return ;
		}
	}
}
