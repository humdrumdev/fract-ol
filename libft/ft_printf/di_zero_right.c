/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_zero_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:37:11 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:49 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "decimal_di.h"
#include "../libft.h"

int	di_zero_right_case1(t_conv_details *det, char special)
{
	int	nrd;

	nrd = (det->is_sign_padded && !det->min_width);
	if (det->is_zero_padded && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if (det->has_blank)
		ft_putchar_fd(' ', 1);
	while (det->min_width-- > 1 + det->is_sign_padded + det->has_blank)
		ft_putchar_fd(special, 1);
	if (det->is_sign_padded && !det->is_zero_padded)
		ft_putchar_fd('+', 1);
	ft_putchar_fd('0', 1);
	if (nrd)
		return (nrd);
	nrd = (det->has_blank && (det->min_width < 1));
	if (nrd)
		return (nrd);
	return (det->has_blank && (det->min_width != 1));
}

int	di_zero_right_case2(t_conv_details *det, char special)
{
	if (det->is_zero_padded && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if (det->has_blank)
		ft_putchar_fd(' ', 1);
	while (det->is_zeroed && det->min_width--)
		ft_putchar_fd(' ', 1);
	while (det->min_width-- > 1 + det->is_sign_padded)
		ft_putchar_fd(special, 1);
	if (det->is_sign_padded && !det->is_zero_padded)
		ft_putchar_fd('+', 1);
	return (0);
}

static inline int	print_if(char special, int condition, int up, int low)
{
	if (condition)
		while (up-- > low)
			ft_putchar_fd(special, 1);
	return (up);
}

int	di_zero_right_case3(t_conv_details *det)
{
	int	width;
	int	prec;
	int	cnd;
	int	cnd2;

	width = det->min_width;
	prec = det->precision;
	cnd = det->precision + det->has_blank + det->is_sign_padded;
	cnd2 = det->has_blank + det->is_sign_padded + det->is_zero_padded;
	if (det->is_sign_padded && (prec >= width))
		ft_putchar_fd('+', 1);
	if (det->has_blank)
		ft_putchar_fd(' ', 1);
	det->precision = print_if('0', prec >= width, det->precision, cnd2 - 1);
	det->min_width = print_if(' ', width > prec, det->min_width, cnd);
	if (det->is_sign_padded && (prec < width))
		ft_putchar_fd('+', 1);
	det->precision = print_if('0', prec < width, det->precision, 0);
	cnd = (det->has_blank && (prec > width));
	return (cnd + ((det->is_sign_padded) && width < prec));
}

int	print_di_zero_right(t_conv_details *det, char special)
{
	if (!det->is_precisioned)
		return (di_zero_right_case1(det, special));
	if (det->is_zeroed)
		return (di_zero_right_case2(det, special));
	else
		return (di_zero_right_case3(det));
}
