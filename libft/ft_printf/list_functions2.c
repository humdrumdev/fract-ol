/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:48:45 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:45:44 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"
#include "lst.h"
#include "parser.h"

int	add_back(t_conv **head, t_conv *new)
{
	t_conv	*tmp;

	if (!head || !new)
		return (-1);
	if (!(*head))
	{
		*head = new;
		return (0);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	clear_list(t_conv **head)
{
	t_conv	*tmp;
	t_conv	*next;

	if (head && *head)
	{
		tmp = *head;
		while (tmp)
		{
			next = tmp->next;
			delete_node(tmp);
			tmp = next;
		}
		*head = NULL;
	}
}
