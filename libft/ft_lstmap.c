/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:36:58 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 11:18:29 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_add_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

static void	*ft_lstclr(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	if (!lst || !(*lst))
		return (NULL);
	curr = (*lst)->next;
	while (curr)
	{
		(*del)(curr->content);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
	return (NULL);
}

t_list	*ft_lstmap(t_list *head, void *(*func)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!head || !func)
		return (NULL);
	if (!del)
		del = free;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (*func)(head->content);
	new->next = NULL;
	head = head->next;
	while (head)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		if (!tmp)
			return (ft_lstclr(&new, del));
		tmp->content = (*func)(head->content);
		tmp->next = NULL;
		ft_add_back(&new, tmp);
		head = head->next;
	}
	return (new);
}
