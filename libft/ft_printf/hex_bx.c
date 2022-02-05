/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_bx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:50:45 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 19:29:51 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "core.h"
#include "utils.h"
#include "hex.h"
#include "../libft.h"
#include <unistd.h>

static inline int	left_put_nbr(t_conv_details *det, int len, int cnd, int n)
{
	if (det->min_width > det->len)
		while (len-- > cnd)
			ft_putchar_fd('0', 1);
	if (!(!n && det->is_zeroed))
		ft_putnbr_base(n, "0123456789ABCDEF", 16);
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
		det->is_hash_padded = write(1, "0X", 2);
	if (!(det->is_zeroed && !num))
	{
		while (det->precision-- > det->len)
			len -= ft_putchar_fd('0', 1);
	}
	if (!num && det->is_zeroed)
		while (len)
			len -= ft_putchar_fd(' ', 1);
	len = left_put_nbr(det, len, cnd2, num);
	while (len >= cnd)
		len -= ft_putchar_fd(special, 1);
}

static void	pad_hex_right(t_conv_details *det, int len, unsigned int num)
{
	if (det->is_hash_padded)
		det->is_hash_padded = write(1, "0X", 2);
	len -= 2 * det->is_hash_padded;
	len += (det->precision > det->len) * (det->min_width - det->precision);
	if (len > det->len && !det->is_zero_padded)
		while (len-- > det->len)
			det->is_hash_padded = ft_putchar_fd('0', 1);
	det->is_hash_padded = ft_putnbr_base(num, "0123456789ABCDEF", 16);
}

static void	right(t_conv_details *det, unsigned int num, int len, char special)
{
	int	cnd;

	if (det->is_zeroed && !num)
	{
		while (det->min_width)
			det->min_width -= ft_putchar_fd(' ', 1);
		return ;
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
			len -= ft_putchar_fd(special, 1);
		while ((len-- > det->len) && (det->min_width-- > det->len))
			ft_putchar_fd('0', 1);
	}
	pad_hex_right(det, len, num);
}

int	print_bx(va_list ap, t_conv_details *det)
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
		right(det, num, len, special);
	else
		normal_hex(num, len, det, "0123456789ABCDEF");
	cnd = 2 * (num && det->is_hash_padded);
	return (len + cnd);
}
