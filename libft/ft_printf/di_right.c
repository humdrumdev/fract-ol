/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:15:54 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:20 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decimal_di.h"
#include "utils.h"
#include "ft_printf.h"

int	di_right_case1(int slen, t_conv_details *det, int num)
{
	int	x;
	int	cnd;

	cnd = ((num > 0) && det->is_sign_padded);
	x = ft_max(slen, det->min_width);
	while (x-- > slen + ((det->is_sign_padded || det->has_blank) && num > 0))
		ft_putchar_fd(' ', 1);
	if (num < 0)
		ft_putchar_fd('-', 1);
	if (num > 0 && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if (num > 0 && !det->is_sign_padded && det->has_blank)
		ft_putchar_fd(' ', 1);
	ft_putint_base(num, "0123456789", 10);
	return (cnd);
}

int	di_right_case2(int num, int prec, int slen, t_conv_details *det)
{
	int	cnd;

	cnd = (det->has_blank || det->is_sign_padded);
	if (num < 0 && cnd)
		ft_putchar_fd('-', 1);
	if (num > 0 && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if (num > 0 && det->has_blank && !det->is_sign_padded)
		ft_putchar_fd(' ', 1);
	if ((num < 0) && !cnd)
		ft_putchar_fd('-', 1);
	while (prec-- > slen - (num < 0))
		ft_putchar_fd('0', 1);
	if (num < 0)
		ft_putnbr_base(-num, "0123456789", 10);
	else
		ft_putnbr_base(num, "0123456789", 10);
	return (cnd + (det->is_zero_padded && num < 0));
}

void	di_right_case3_prec(int num, t_conv_details *det, int prec)
{
	if (num < 0 && det->is_zero_padded && det->is_precisioned)
		ft_putchar_fd('-', 1);
	if (num < 0 && !det->is_zero_padded)
		ft_putchar_fd('-', 1);
	if (num > 0 && det->is_sign_padded && !det->is_zero_padded)
		ft_putchar_fd('+', 1);
	if (ft_min(det->len, prec) == det->len)
		while (prec-- > det->len - (num < 0))
			ft_putchar_fd('0', 1);
	if (num < 0)
		ft_putnbr_base(-num, "0123456789", 10);
	else
		ft_putnbr_base(num, "0123456789", 10);
}

int	di_right_case3(int width, int num, t_conv_details *det, int prec)
{
	char	special;
	int		cnd;
	int		cnd2;
	int		cnd3;

	cnd = ((num > 0) && (det->is_sign_padded || det->has_blank));
	cnd = (cnd || ((num < 0) && !det->has_blank));
	cnd = (cnd || ((num < 0) && (prec > det->len)));
	cnd2 = (cnd && !((num < 0) && (width > ft_max(prec, det->len))));
	cnd3 = (num < 0 && det->is_zero_padded && det->precision);
	cnd2 = (cnd2 || cnd3);
	cnd3 = (cnd3 && (det->precision < det->len));
	special = ' ';
	if (det->is_zero_padded && !det->precision)
		special = '0';
	if (num < 0 && det->is_zero_padded && !det->is_precisioned)
		ft_putchar_fd('-', 1);
	if (num > 0 && det->is_sign_padded && det->is_zero_padded)
		ft_putchar_fd('+', 1);
	if (num > 0 && det->has_blank && !det->is_sign_padded)
		ft_putchar_fd(' ', 1);
	while (width-- > ft_max(det->len, prec) + cnd2 - cnd3)
		ft_putchar_fd(special, 1);
	return (di_right_case3_prec(num, det, prec), 0);
}

void	di_right_general(int num, t_conv_details *det, int prec, int slen)
{
	int	cnd;

	cnd = (det->is_zero_padded || (det->has_blank && !det->is_zero_padded));
	cnd = (cnd || det->is_sign_padded);
	if (num < 0 && cnd)
		ft_putchar_fd('-', 1);
	if (num > 0 && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if (num > 0 && det->has_blank && !det->is_sign_padded)
		ft_putchar_fd(' ', 1);
	while (prec-- > slen - (num < 0) + (det->is_sign_padded && num > 0))
		ft_putchar_fd(' ', 1);
	if (num < 0)
		ft_putnbr_base(-num, "0123456789", 10);
	else
		ft_putnbr_base(num, "0123456789", 10);
}
