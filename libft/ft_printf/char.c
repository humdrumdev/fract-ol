/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:22:37 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:41:19 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char.h"
#include "../libft.h"
#include <stdarg.h>
#include "core.h"

int	print_char(va_list ap, t_conv_details *det)
{
	int				len;
	unsigned char	c;
	char			special;
	int				ret;

	c = (unsigned char)va_arg(ap, int);
	special = get_padding(det);
	len = 1;
	if (det->len)
		len = det->len;
	ret = len;
	len--;
	if (det->is_padded_to_left)
	{
		ft_putchar_fd(c, 1);
		while (len--)
			ft_putchar_fd(special, 1);
	}
	else
	{
		while (len--)
			ft_putchar_fd(special, 1);
		ft_putchar_fd(c, 1);
	}
	return (ret);
}
