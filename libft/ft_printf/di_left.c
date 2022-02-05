/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_left.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:15:50 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:00 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decimal_di.h"
#include <stdio.h>
#include "../libft.h"
#include "utils.h"

int	print_di_left_case1(int num, int len, int slen, t_conv_details *det)
{
	int	cnd;
	int	cnd2;
	int	cnd3;

	cnd = ((num > 0) && (det->has_blank || det->is_sign_padded));
	cnd2 = ((len == slen) && cnd);
	cnd3 = ((num < 0) && (det->min_width == slen));
	cnd3 = (cnd3 && !det->is_zeroed && det->is_precisioned);
	if ((num > 0) && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if ((num > 0) && det->has_blank && !det->is_sign_padded)
		ft_putchar_fd(' ', 1);
	if (num < 0)
		ft_putchar_fd('-', 1);
	if (cnd3)
		ft_putchar_fd('0', 1);
	ft_putint_base(num, "0123456789", 10);
	while (len-- > slen + cnd)
		ft_putchar_fd(' ', 1);
	return (cnd2);
}

int	di_left_prec(int num, int len, t_conv_details *det)
{
	int	cnd;

	cnd = (det->has_blank || det->is_sign_padded);
	if ((num > 0) && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if ((num > 0) && det->has_blank && !det->is_sign_padded)
		ft_putchar_fd(' ', 1);
	if (num < 0)
		ft_putchar_fd('-', 1);
	while (len-- > (det->len - (num < 0)))
		ft_putchar_fd('0', 1);
	ft_putint_base(num, "0123456789", 10);
	return (cnd + (num < 0 && !cnd));
}

int	di_left_width(int num, int len, t_conv_details *det)
{
	int	x;
	int	cnd;
	int	cnd2;

	cnd = ((num < 0) && (det->len <= det->precision));
	cnd2 = ((num > 0) && (det->has_blank || det->is_sign_padded));
	di_left_prec(num, det->precision, det);
	x = len - ft_max(det->precision, det->len);
	while (x-- > (cnd || cnd2))
		ft_putchar_fd(' ', 1);
	return (0);
}
