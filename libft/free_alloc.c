/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:26:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 20:21:57 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_b(t_mem **list, void *alloced)
{
	t_mem	*new;

	new = (t_mem *)malloc(sizeof(t_mem));
	if (!new)
		return (-1);
	new->content = alloced;
	new->next = NULL;
	if (!*list)
	{
		new->last = new;
		*list = new;
	}
	else
	{
		(*list)->last->next = new;
		(*list)->last = new;
	}
	return (0);
}

static void	lstclear(t_mem **list)
{
	t_mem	*curr;
	t_mem	*next;

	if (*list)
	{
		curr = (*list)->next;
		while (curr)
		{
			next = curr->next;
			free(curr->content);
			free(curr);
			curr = next;
		}
		free((*list)->content);
		free(*list);
		*list = NULL;
	}
}

int	free_alloc(void **to_alloc, size_t size)
{
	static t_mem	*memptr;

	if (!to_alloc)
		return (lstclear(&memptr), 0);
	*to_alloc = malloc(size);
	if (!*to_alloc)
		return (lstclear(&memptr), -1);
	if (add_b(&memptr, *to_alloc))
		return (lstclear(&memptr), -1);
	return (0);
}
