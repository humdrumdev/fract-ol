/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:23:45 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/02 20:04:47 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	if (!lst || !(*lst) || !del)
		return ;
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
}
