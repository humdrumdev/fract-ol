/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_zero_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:35:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:27 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "../libft.h"

static inline int	di_zero_left_case1(t_conv_details *det, char special)
{
	int	cnd;

	cnd = (det->is_sign_padded);
	if (det->has_blank)
		ft_putchar_fd(' ', 1);
	if (!det->has_blank && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	ft_putchar_fd('0', 1);
	while (det->min_width-- > 1 + cnd + det->has_blank)
		ft_putchar_fd(special, 1);
	if (det->min_width == 2 && det->has_blank)
		return (1);
	if (det->min_width == 1 && det->has_blank)
		return (0);
	return (det->has_blank && !det->is_sign_padded);
}

static inline int	di_zero_left_case2(t_conv_details *det, char special)
{
	int	width;

	width = det->min_width;
	if (det->has_blank)
		ft_putchar_fd(' ', 1);
	if (!det->has_blank && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	while (det->min_width-- > det->is_sign_padded)
		ft_putchar_fd(special, 1);
	return (-(width == 0 && !det->has_blank && !det->is_sign_padded));
}

static void	di_zero_w_p(t_conv_details *det, int cnd, int cnd2, int cnd3)
{
	int	cnd4;
	int	width;
	int	prec;

	width = det->min_width;
	prec = det->precision;
	cnd4 = (prec < width);
	cnd4 = (!cnd && !det->has_blank && !det->is_sign_padded);
	cnd4 = cnd4 + det->has_blank + det->is_sign_padded;
	if (prec >= width)
		while (det->precision-- >= cnd4)
			ft_putchar_fd('0', 1);
	if (width > prec)
	{
		while ((det->min_width-- > (width - prec + cnd)))
			ft_putchar_fd('0', 1);
		while (det->min_width-- > cnd + det->has_blank)
			ft_putchar_fd(' ', 1);
		if ((!det->has_blank && !cnd2) || cnd3)
			ft_putchar_fd(' ', 1);
	}
}

static int	di_zero_left_case3(t_conv_details *det)
{
	int	cnd;
	int	cnd2;
	int	cnd3;
	int	prec;
	int	width;

	prec = det->precision;
	width = det->min_width;
	cnd = (det->precision < det->min_width);
	cnd2 = (cnd && det->is_sign_padded && !det->has_blank);
	cnd3 = (det->has_blank && (width > prec));
	if (det->has_blank)
		ft_putchar_fd(' ', 1);
	if (!det->has_blank && det->is_sign_padded)
		ft_putchar_fd('+', 1);
	if (det->precision < det->min_width)
		ft_putchar_fd('0', 1);
	di_zero_w_p(det, cnd, cnd2, cnd3);
	if (prec == width && width > 1)
		return (det->has_blank || det->is_sign_padded);
	return ((det->has_blank && (width < prec)) + det->is_sign_padded - cnd2);
}

int	print_di_zero_left(t_conv_details *det, char special)
{
	if (!det->is_precisioned)
		return (di_zero_left_case1(det, special));
	if (det->is_zeroed)
		return (di_zero_left_case2(det, special));
	else
		return (di_zero_left_case3(det));
}
