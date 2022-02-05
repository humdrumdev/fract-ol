/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 04:37:47 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:45:37 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"
#include "lst.h"

char	*get_new_string(int beg, int end, const char *s)
{
	char	*new;

	new = (char *)malloc((end - beg + 1) * sizeof(char));
	if (new)
	{
		if (end > beg)
			new = ft_memcpy(new, s + beg, end - beg);
		new[end - beg] = '\0';
	}
	return (new);
}

void	delete_node(t_conv *node)
{
	if (node)
	{
		if (node->flags)
			free(node->flags);
		if (node->width)
			free(node->width);
		if (node->precision)
			free(node->precision);
		free(node);
	}
}

t_conv	*new_simple_node(int beg, int end, const char *format)
{
	t_conv	*new;

	new = (t_conv *)malloc(sizeof(t_conv));
	if (new)
	{
		new->flags = get_new_string(beg, end, format);
		if (!(new->flags))
			return (free(new), NULL);
		new->type = 0;
		new->width = NULL;
		new->precision = NULL;
		new->next = NULL;
	}
	return (new);
}

int	set_property(t_conv *new, t_beg_n_end b_e[3], const char *format)
{
	new->flags = NULL;
	new->width = NULL;
	new->precision = NULL;
	new->next = NULL;
	if (b_e[0].start < b_e[0].end)
	{
		new->flags = get_new_string(b_e[0].start, b_e[0].end, format);
		if (!(new->flags))
			return (delete_node(new), 1);
	}
	if (b_e[1].start < b_e[1].end)
	{
		new->width = get_new_string(b_e[1].start, b_e[1].end, format);
		if (!(new->width))
			return (delete_node(new), 1);
	}
	if (b_e[2].start < b_e[2].end || b_e[2].is_zero)
	{
		new->precision = get_new_string(b_e[2].start, b_e[2].end, format);
		if (!(new->precision))
			return (delete_node(new), 1);
	}
	return (0);
}

t_conv	*new_node(t_beg_n_end b_e[3], const char *format, char type)
{
	t_conv	*new;

	new = (t_conv *)malloc(sizeof(t_conv));
	if (new)
	{
		new->type = type;
		if (set_property(new, b_e, format))
			return (NULL);
	}
	return (new);
}
