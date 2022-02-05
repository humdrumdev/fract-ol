/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:14:26 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:46:12 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "percent.h"
#include "../libft.h"
#include "core.h"

static void	left(int len, char special)
{
	ft_putchar_fd('%', 1);
	while (len-- > 1)
		ft_putchar_fd(special, 1);
}

static void	normal(int len, char special)
{
	while (len-- > 1)
		ft_putchar_fd(special, 1);
	ft_putchar_fd('%', 1);
}

int	print_percent(t_conv_details *det)
{
	int		ret;
	int		len;
	char	special;

	special = get_padding(det);
	if (det->is_space_padded && det->is_zero_padded && !det->is_sign_padded)
		special = '0';
	if (special == '0' && det->is_padded_to_left)
		special = ' ';
	len = 1;
	if (det->min_width)
		len = det->min_width;
	ret = len;
	if (det->is_padded_to_left)
		left(len, special);
	else
		normal(len, special);
	return (ret);
}
