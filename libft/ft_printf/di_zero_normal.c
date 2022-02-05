/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_zero_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:20:51 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:39 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "utils.h"
#include "ft_printf.h"

static inline int	put_special(int start, int end, char special)
{
	while (start-- > end)
		ft_putchar_fd(special, 1);
	return (start);
}

static int	di_zero_case1(t_conv_details *det, int len)
{
	if (det->is_space_padded)
		put_special(len, 0, ' ');
	if (det->is_sign_padded)
		ft_putchar_fd('+', 1);
	else
		while (det->min_width--)
			ft_putchar_fd(' ', 1);
	return (0);
}

static int	di_zero_case2(t_conv_details *det)
{
	if (det->is_space_padded)
		ft_putchar_fd(' ', 1);
	if (det->is_sign_padded)
		ft_putchar_fd('+', 1);
	ft_putchar_fd('0', 1);
	return ((det->is_space_padded + det->is_sign_padded));
}

int	di_zero_cases(t_conv_details *det, int len, char special)
{
	if (det->is_zeroed && det->min_width)
		return (di_zero_case1(det, len));
	if (!det->is_precisioned && !det->min_width)
		return (di_zero_case2(det));
	if (!det->is_precisioned && det->min_width)
	{
		put_special(len, 1, special);
		ft_putchar_fd('0', 1);
		return (0);
	}
	if (det->is_precisioned && (det->min_width >= det->precision))
	{
		len = put_special(len, det->precision, ' ');
		put_special(len, -1, '0');
		return (0);
	}
	if (det->min_width && det->min_width < det->precision)
		return (put_special(len, 0, '0'), 0);
	return (-1);
}
