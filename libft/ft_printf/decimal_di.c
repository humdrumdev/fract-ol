/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:20:01 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:42:45 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decimal_di.h"
#include "core.h"
#include "utils.h"
#include "../libft.h"
#include <stdio.h>

int	print_di_right(t_conv_details *det, int num)
{
	int	width;
	int	prec;
	int	slen;

	width = det->min_width;
	prec = det->precision;
	slen = det->len;
	if (det->is_zeroed)
		return (di_right_case1(slen, det, num));
	if (prec >= ft_max(width, slen))
		return (di_right_case2(num, prec, slen, det));
	if (width >= ft_max(slen, prec))
		return (di_right_case3(width, num, det, prec));
	di_right_general(num, det, prec, slen);
	return ((num > 0) && (det->has_blank || det->is_sign_padded));
}

int	print_di_zero(int len, t_conv_details *det, char special)
{
	int	ret;

	if (det->is_padded_to_left)
		return (print_di_zero_left(det, special));
	else if (det->is_padded_to_right)
		return (print_di_zero_right(det, special));
	else
	{
		ret = di_zero_cases(det, len, special);
		if (ret >= 0)
			return (ret);
		if (det->precision && !det->min_width)
			while (det->precision--)
				ft_putchar_fd('0', 1);
		if (!det->min_width && det->is_zeroed)
			return (-1);
	}
	return (0);
}

int	print_di_left(int len, t_conv_details *det, int num)
{
	if (det->is_zeroed || (len == det->len && !det->precision))
		return (print_di_left_case1(num, len, det->len, det));
	if (len == det->precision)
		return (di_left_prec(num, len, det));
	return (di_left_width(num, len, det));
}

int	print_di_normal(t_conv_details *det, int num)
{
	int	ret;
	int	width;
	int	prec;
	int	slen;

	ret = num < 0;
	width = det->min_width;
	prec = det->precision;
	slen = det->len;
	if (det->is_zeroed)
		return (di_normal_case1(slen, width, num));
	if (prec >= ft_max(width, slen))
		return (ret + di_normal_case2(num, prec, slen));
	if (width >= ft_max(slen, prec))
		return (di_normal_case3(width, num, slen, prec));
	if (num < 0)
		ft_putchar_fd('-', 1);
	while (prec-- > slen - (num < 0))
		ft_putchar_fd('0', 1);
	if (num < 0)
		ft_putnbr_base(-num, "0123456789", 10);
	else
		ft_putnbr_base(num, "0123456789", 10);
	return (0);
}

int	print_d_or_i(va_list ap, t_conv_details *det)
{
	int		len;
	int		slen;
	int		num;
	char	special;

	num = va_arg(ap, int);
	if (num >= 0)
		slen = num_size(num, 10);
	else
		slen = num_size(-num, 10) + 1;
	len = ft_max(ft_max(slen, det->precision), det->min_width);
	special = get_padding(det);
	if (!num && det->is_zeroed && !det->min_width)
		return (0);
	if (!num)
		return (len + print_di_zero(len, det, special));
	det->len = slen;
	if (det->is_padded_to_left)
		return (len + print_di_left(len, det, num));
	else if (det->is_padded_to_right)
		return (len + print_di_right(det, num));
	else
		return (len + print_di_normal(det, num));
	return (-1 * len);
}
