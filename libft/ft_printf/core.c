/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:24:15 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 19:29:01 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <stdarg.h>
#include <unistd.h>
#include "../libft.h"
#include "flags.h"
#include "utils.h"
#include "lst.h"
#include "ft_printf.h"

int	print_type(va_list ap, t_conv_details *det, char type)
{
	if (type == '%')
		return (print_percent(det));
	if (type == 'c')
		return (print_char(ap, det));
	if (type == 's')
		return (print_str(ap, det));
	if (type == 'p')
		return (print_ptr(ap, det));
	if (type == 'd' || type == 'i')
		return (print_d_or_i(ap, det));
	if (type == 'u')
		return (print_u(ap, det));
	if (type == 'x')
		return (print_x(ap, det));
	if (type == 'X')
		return (print_bx(ap, det));
	return (-1);
}

int	print_node(t_conv *conv, va_list ap)
{
	t_conv_details	*det;
	int				len;
	int				cnd;

	cnd = (conv->precision && *(conv->precision));
	if (conv->type == 0)
	{
		ft_putstr_fd(conv->flags, 1);
		len = ft_strlen(conv->flags);
	}
	else
	{
		det = conv_handler(conv, ap);
		if (!det)
			return (-1);
		if ((conv->type == 'c' || conv->type == 'p') && cnd)
			return (free(det), -1);
		len = print_type(ap, det, conv->type);
		free(det);
	}
	return (len);
}

int	check_for_errors(t_conv *conv)
{
	t_conv_details	*det;

	while (conv)
	{
		if (conv->type)
		{
			if ((conv->type == 'c' || conv->type == 'p'))
				if (conv->precision && *(conv->precision))
					return (-1);
			det = (t_conv_details *)malloc(sizeof(t_conv_details));
			if (!det)
				return (-1);
			init_conv_details(det);
			if (flag_handler(conv->type, conv->flags, det) == -1)
				return (free(det), -1);
			free(det);
		}
		conv = conv->next;
	}
	return (0);
}

char	get_padding(t_conv_details *det)
{
	char	special;

	special = ' ';
	if (det->is_zero_padded && !(det->is_precisioned))
		special = '0';
	if (det->is_space_padded)
		special = ' ';
	if (det->is_zero_padded && det->is_precisioned)
	{
		special = '0';
		if (det->min_width > det->precision)
			special = ' ';
	}
	return (special);
}

int	normal_hex(int num, int len, t_conv_details *det, char *base)
{
	int	size;

	size = 0;
	while (len-- > det->len)
		size += ft_putchar_fd('0', 1);
	if (det->is_hash_padded && num)
	{
		if (contains(base, 'A'))
			size += write(1, "0X", 2);
		else
			size += write(1, "0x", 2);
	}
	return (size + ft_putnbr_base(num, base, 16));
}
