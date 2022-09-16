/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:16:37 by kshim             #+#    #+#             */
/*   Updated: 2022/09/16 12:54:26 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (new_elem == 0)
		return (0);
	new_elem -> content = content;
	new_elem -> next = 0;
	return (new_elem);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	end = 0;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	end = ft_lstlast(*lst);
	end -> next = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del != 0)
		del(lst -> content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;

	now = 0;
	while (*lst != 0)
	{
		now = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = now;
	}
	*lst = 0;
	return ;
}
