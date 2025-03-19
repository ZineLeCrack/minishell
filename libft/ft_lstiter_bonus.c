/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:18:23 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/11 15:19:45 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include "ft_lstnew.c"
#include "ft_lstadd_front.c"

void add(void *content)
{
	(*(int *)content)++;
}


void print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d -> ", *(int *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}


int main()
{
	int i = 0;
	t_list *liste = NULL;

	while (i < 5)
	{
		int *value = malloc(sizeof(int));
		*value = i;
		ft_lstadd_front(&liste, ft_lstnew((void *)value));
		i++;
	}

	printf("Contenu de la liste : ");
	print_list(liste);

	ft_lstiter(liste, add);
	printf("Liste apres application de la fonction : ");
	print_list(liste);

	return 0;
}
*/