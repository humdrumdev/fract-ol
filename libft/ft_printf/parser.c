/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:31:58 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:45:59 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"
#include "parser.h"
#include "lst.h"
#include "utils.h"

static void	init_beg_n_end(t_beg_n_end beg_end[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		beg_end[i].start = 0;
		beg_end[i].end = 0;
		beg_end[i].is_zero = 0;
		i++;
	}
}

static void	get_precision(const char *format, t_beg_n_end beg_end[3], int *i)
{
	beg_end[2].start = ++(*i);
	if (format[*i] == '*')
		(*i)++;
	else
	{
		if (format[*i] == '-')
			(*i)++;
		while (ft_isdigit(format[*i]))
			(*i)++;
	}
	beg_end[2].end = *i;
	if (*i == beg_end[2].start)
		beg_end[2].is_zero = 1;
}

int	get_beg_n_ends(const char *format, t_beg_n_end beg_end[3], int i)
{
	init_beg_n_end(beg_end);
	beg_end[0].start = i;
	while (contains(FLAGS, format[i]))
		i++;
	beg_end[0].end = i;
	beg_end[1].start = i;
	if (format[i] == '*')
		i++;
	else
		while (ft_isdigit(format[i]))
			i++;
	beg_end[1].end = i;
	if (format[i] == '.')
		get_precision(format, beg_end, &i);
	return (i);
}

t_conv	*parse_format(const char *format)
{
	int			i;
	t_beg_n_end	beg_end[3];
	t_conv		*convs;
	int			beg;

	i = -1;
	convs = NULL;
	while (format[++i])
	{
		beg = i;
		while (format[i] && format[i] != '%')
			i++;
		if (i > beg && add_back(&convs, new_simple_node(beg, i, format)) == -1)
			return (clear_list(&convs), NULL);
		if (!format[i])
			return (convs);
		i = get_beg_n_ends(format, beg_end, i + 1);
		if (!contains(TYPES, format[i]))
			return (clear_list(&convs), NULL);
		if (add_back(&convs, new_node(beg_end, format, format[i])) == -1)
			return (clear_list(&convs), NULL);
	}
	if (i == 0)
		return (new_simple_node(0, 0, ""));
	return (convs);
}
