/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_int.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:18:47 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:46:42 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "u_int.h"
#include "utils.h"
#include "ft_printf.h"

static void	left_normal(unsigned int n, int len, t_conv_details *det, char s)
{
	if (!n && det->precision)
	{
		while ((det->precision-- > 0) && len-- > 1)
			ft_putchar_fd('0', 1);
		while (len-- > 0)
			ft_putchar_fd(' ', 1);
	}
	if (!n)
		while (len-- > 0)
			ft_putchar_fd(' ', 1);
	while (det->precision-- > det->len && len-- > 0)
		ft_putchar_fd('0', 1);
	if (n)
		ft_putnbr_base(n, "0123456789", 10);
	while (len-- > det->len)
		ft_putchar_fd(s, 1);
}

static void	left(unsigned int num, int len, t_conv_details *det, char special)
{
	if (!det->is_precisioned)
	{
		ft_putnbr_base(num, "0123456789", 10);
		while (len-- > det->len)
			ft_putchar_fd(' ', 1);
	}
	else if (det->is_zeroed)
	{
		if (num)
			ft_putnbr_base(num, "0123456789", 10);
		while (len-- > det->len - (num == 0))
			ft_putchar_fd(' ', 1);
	}
	else if (det->is_precisioned && det->min_width <= det->precision)
	{
		while (len-- > det->len)
			ft_putchar_fd('0', 1);
		ft_putnbr_base(num, "0123456789", 10);
	}
	else
		left_normal(num, len, det, special);
}

static inline void	width_prevalent(t_conv_details *det, int len, char s, int n)
{
	int	cnd;

	cnd = ((det->precision > det->len));
	if (det->precision > det->len)
		while (len-- > det->precision)
			ft_putchar_fd(' ', 1);
	while (len-- > (det->len - cnd))
		ft_putchar_fd(s, 1);
	ft_putnbr_base(n, "0123456789", 10);
}

static inline void	right(unsigned int n, int len, t_conv_details *det, char s)
{
	int	cnd;

	cnd = (det->is_zero_padded && (det->precision > det->len));
	s = s * !cnd + '0' * cnd;
	if (det->is_zeroed || (det->is_precisioned && !det->precision))
	{
		if (n)
		{
			while (det->min_width-- > det->len)
				ft_putchar_fd(' ', 1);
			ft_putnbr_base(n, "0123456789", 10);
		}
		while (!n && det->min_width-- > 0 && len--)
			ft_putchar_fd(' ', 1);
	}
	else if (det->min_width > ft_max(det->precision, det->len))
		width_prevalent(det, len, s, n);
	else
	{
		while (len-- > det->len)
			ft_putchar_fd(s, 1);
		ft_putnbr_base(n, "0123456789", 10);
	}
}

int	print_u(va_list ap, t_conv_details *det)
{
	int				len;
	int				slen;
	unsigned int	num;
	char			special;

	num = va_arg(ap, unsigned int);
	slen = num_size(num, 10);
	len = ft_max(ft_max(slen, det->len), det->precision);
	special = get_padding(det);
	det->len = slen;
	if (!num && det->is_zeroed && !det->min_width)
		return (0);
	if (det->is_padded_to_left)
		left(num, len, det, special);
	else if (det->is_padded_to_right)
		right(num, len, det, special);
	else
	{
		if (det->min_width > slen)
			special = ' ';
		if (det->precision > slen)
			special = '0';
		right(num, len, det, special);
	}
	return (len);
}
