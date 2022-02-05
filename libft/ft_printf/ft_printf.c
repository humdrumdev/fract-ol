/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:54:49 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:44:10 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include <stdarg.h>
#include <stdio.h>
#include "parser.h"
#include "core.h"
#include "utils.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_conv	*convs;
	t_conv	*tmp;
	int		len;
	int		conv_len;

	convs = parse_format(format);
	if (!convs)
		return (-1);
	if (check_for_errors(convs) == -1)
		return (clear_list(&convs), -1);
	tmp = convs;
	len = 0;
	va_start(ap, format);
	while (tmp)
	{
		conv_len = print_node(tmp, ap);
		if (conv_len == -1)
			return (clear_list(&convs), -1);
		len += conv_len;
		tmp = tmp->next;
	}
	va_end(ap);
	clear_list(&convs);
	return (len);
}
