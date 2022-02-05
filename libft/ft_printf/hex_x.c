/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:50:20 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 16:11:12 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "core.h"
#include "utils.h"
#include "../libft.h"
#include "hex.h"
#include <unistd.h>
#include <stdio.h>

static inline int	left_put_nbr(t_conv_details *det, int len, int cnd, int n)
{
	if (det->min_width > det->len)
		while (len-- > cnd)
			ft_putchar_fd('0', 1);
	if (!(!n && det->is_zeroed))
		ft_putnbr_base(n, "0123456789abcdef", 16);
	return (len);
}

static void	left(t_conv_details *det, int len, int num, char special)
{
	int	cnd;
	int	cnd2;

	cnd = 2 * det->is_hash_padded + det->len + (det->min_width <= det->len);
	cnd2 = ft_max(ft_max(det->min_width, det->len), det->precision);
	cnd2 -= 2 * det->is_hash_padded;
	if (det->is_hash_padded)
		det->is_hash_padded = write(1, "0x", 2);
	if (!(det->is_zeroed && !num) && (det->precision > det->len))
	{
		while (det->precision-- > det->len)
		{
			ft_putchar_fd('0', 1);
			len--;
		}
	}
	if (!num && det->is_zeroed)
		while (len--)
			ft_putchar_fd(' ', 1);
	len = left_put_nbr(det, len, cnd2, num);
	while (len-- >= cnd)
		ft_putchar_fd(special, 1);
}

static int	pad_hex_right(t_conv_details *det, int len, unsigned int num)
{
	int	cnd;

	cnd = (!num && (det->min_width > det->precision));
	cnd = 2 * (cnd && (det->precision && det->is_hash_padded));
	if (det->is_hash_padded && !cnd)
		det->is_hash_padded = write(1, "0x", 2);
	if (cnd)
		cnd = -2 + write(1, "  ", 2);
	len -= 2 * det->is_hash_padded;
	len += (det->precision > det->len) * (det->min_width - det->precision);
	if (len > det->len && !det->is_zero_padded)
		while (len-- > det->len)
			cnd = -1 + ft_putchar_fd('0', 1);
	len = ft_putnbr_base(num, "0123456789abcdef", 16);
	return (cnd);
}

static int	right(t_conv_details *det, int num, int len, char special)
{
	int	cnd;

	if (det->is_zeroed && !num)
	{
		while (det->min_width--)
			ft_putchar_fd(' ', 1);
		return (0);
	}
	cnd = ft_min(ft_max(det->len, det->precision), det->min_width);
	if (!cnd)
		cnd = ft_min(det->len, det->precision);
	if (det->precision == len)
	{
		special = '0';
		cnd -= (det->min_width != 0) * (det->precision - det->min_width + 1);
		cnd -= ((det->min_width == len));
	}
	if (len > det->len)
	{
		while (len > ft_max(det->len, cnd + 2 * det->is_hash_padded))
			ft_putchar_fd(special, 1 && len--);
		while ((len-- > det->len) && (det->min_width-- > det->len))
			ft_putchar_fd('0', 1);
	}
	return (pad_hex_right(det, len, num));
}

int	print_x(va_list ap, t_conv_details *det)
{
	int				len;
	int				cnd;
	unsigned int	num;
	char			special;

	num = va_arg(ap, unsigned int);
	if (!num && det->is_zeroed && !det->min_width)
		return (0);
	det->len = num_size(num, 16);
	len = ft_max(det->min_width, ft_max(det->precision, det->len));
	special = get_padding(det);
	if (det->is_padded_to_left)
		left(det, len, num, special);
	else if (det->is_padded_to_right || det->min_width)
		len -= right(det, num, len, special);
	else
		normal_hex(num, len, det, "0123456789abcdef");
	cnd = 2 * (num && det->is_hash_padded);
	return (len + cnd);
}
