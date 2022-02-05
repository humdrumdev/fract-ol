/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_normal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:50:07 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:11 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decimal_di.h"
#include "utils.h"
#include "ft_printf.h"

int	di_normal_case1(int slen, int width, int num)
{
	int	x;

	x = ft_max(slen, width);
	while (x-- > slen)
		ft_putchar_fd(' ', 1);
	if (num < 0)
		ft_putchar_fd('-', 1);
	ft_putint_base(num, "0123456789", 10);
	return (0);
}

int	di_normal_case2(int num, int prec, int slen)
{
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

int	di_normal_case3(int width, int num, int slen, int prec)
{
	int	x;

	while (width-- > ft_max(slen, prec) + ((num < 0) && prec >= slen))
		ft_putchar_fd(' ', 1);
	if (num < 0)
		ft_putchar_fd('-', 1);
	x = ft_min(slen, prec);
	if (x == slen)
		while (prec-- > slen - (num < 0))
			ft_putchar_fd('0', 1);
	if (num < 0)
		ft_putnbr_base(-num, "0123456789", 10);
	else
		ft_putnbr_base(num, "0123456789", 10);
	return (0);
}
