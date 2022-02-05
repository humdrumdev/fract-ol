/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:27:14 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:46:25 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "utils.h"
#include "ft_printf.h"

static int	print_loop(int start, int end, char special, int direct)
{
	if (direct)
	{
		while (start-- > end)
			ft_putchar_fd(special, 1);
		return (start);
	}
	else
	{
		while (start++ < end)
			ft_putchar_fd(special, 1);
		return (start);
	}
}

static int	pad_to_right(int len, t_conv_details *det, char special, char *s)
{
	int	i;
	int	j;

	i = 0;
	if (det->is_zeroed)
		return (print_loop(len, 0, special, 1));
	if (!det->is_precisioned)
		return (print_loop(len, det->len, special, 1), ft_putstr_fd(s, 1), 0);
	if (det->min_width >= det->len)
	{
		while (i < len - det->precision && ++i)
			ft_putchar_fd(special, 1);
		j = 0;
		while (i++ < len && s[j])
			ft_putchar_fd(s[j++], 1);
		return (print_loop(i, len, ' ', 0), 0);
	}
	while (len-- > det->precision)
		ft_putchar_fd(special, 1);
	i = 0;
	while (i++ < det->precision && s[i - 1])
		ft_putchar_fd(s[i - 1], 1);
	return (print_loop(i, len, ' ', 0), 0);
}

static void	pad_to_left(int len, char special, char *s, t_conv_details *det)
{
	int	i;

	i = 0;
	if (det->is_zeroed)
		print_loop(len, 0, special, 1);
	else if (!det->is_precisioned)
	{
		ft_putstr_fd(s, 1);
		while (len-- > det->len)
			ft_putchar_fd(special, 1);
	}
	else if (det->min_width >= det->len)
	{
		while (i < det->precision && s[i] && i++ < len)
			ft_putchar_fd(s[i - 1], 1);
		while (i++ < len)
			ft_putchar_fd(special, 1);
	}
	else
	{
		while ((i < det->precision) && s[i++])
			ft_putchar_fd(s[i - 1], 1);
		print_loop(i, len, special, 0);
	}
}

static int	get_len(t_conv_details *det, int slen)
{
	if (!det->is_precisioned)
		return (ft_max(slen, det->min_width));
	else if (det->is_zeroed)
		return (det->min_width);
	else
	{
		if (!det->min_width)
			return (ft_min(slen, det->precision));
		if (det->min_width >= slen)
			return (det->min_width);
		if (det->min_width < slen && det->min_width > det->precision)
			return (det->min_width);
		return (ft_min(slen, det->precision));
	}
}

int	print_str(va_list ap, t_conv_details *det)
{
	int		len;
	char	*s;
	char	special;

	s = va_arg(ap, char *);
	if (!s)
		s = (char *)"(null)";
	special = get_padding(det);
	det->len = ft_strlen(s);
	len = get_len(det, det->len);
	if (det->is_zeroed)
	{
		det->len = 0;
		det->precision = 0;
	}
	if (det->is_padded_to_left)
		pad_to_left(len, special, s, det);
	else
		pad_to_right(len, det, special, s);
	return (len);
}
