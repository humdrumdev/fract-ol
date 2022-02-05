/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:40:54 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:47:07 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_p.h"
#include "../libft.h"
#include "utils.h"

static void	left(void *p, int len, int slen)
{
	ft_putstr_fd("0x", 1);
	put_longnum_base_fd(1, (unsigned long)p, "0123456789abcdef", 16);
	while (len-- > slen)
		ft_putchar_fd(' ', 1);
}

static void	right(void *p, int len, int slen)
{
	while (len-- > slen)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd("0x", 1);
	put_longnum_base_fd(1, (unsigned long)p, "0123456789abcdef", 16);
}

static void	normal(void *p)
{
	ft_putstr_fd("0x", 1);
	put_longnum_base_fd(1, (unsigned long)p, "0123456789abcdef", 16);
}

int	print_ptr(va_list ap, t_conv_details *det)
{
	int		len;
	int		cnd;
	int		slen;
	void	*p;

	p = va_arg(ap, void *);
	slen = long_size((unsigned long)p, 16) + 2;
	len = slen;
	cnd = (det->is_padded_to_right || (det->min_width && !det->is_precisioned));
	if (det->len)
		len = ft_max(det->len, slen);
	if (det->is_padded_to_left)
		left(p, len, slen);
	else if (cnd)
		right(p, len, slen);
	else
		normal(p);
	return (len);
}
