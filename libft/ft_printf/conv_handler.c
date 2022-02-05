/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:29:02 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:42:03 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "flags.h"
#include "utils.h"
#include "../libft.h"

static t_conv_details	*create_det_n_set_flags(t_conv *conv)
{
	t_conv_details	*det;

	det = (t_conv_details *)malloc(sizeof(t_conv_details));
	if (!det)
		return (NULL);
	init_conv_details(det);
	if (flag_handler(conv->type, conv->flags, det) == -1)
		return (free(det), NULL);
	return (det);
}

static void	get_prec(t_conv_details *det, t_conv *conv)
{
	det->len = ft_atoi(conv->precision);
	det->precision = det->len;
	if (!det->precision)
		det->is_zeroed = 1;
	det->is_precisioned = 1;
}

static void	width_n_prec_from_args(t_conv *conv, va_list ap)
{
	int		tmp;
	char	*stmp;

	if (conv->width && contains(conv->width, '*'))
	{
		tmp = va_arg(ap, int);
		if (tmp < 0 && get_absv(&tmp))
		{
			if (!conv->flags || !contains(conv->flags, '-'))
			{
				stmp = ft_strjoin(conv->flags, "-");
				conv->flags = (free(conv->flags), stmp);
			}
		}
		conv->width = (free(conv->width), ft_itoa(tmp));
	}
	if (conv->precision && contains(conv->precision, '*'))
	{
		tmp = va_arg(ap, int);
		if (tmp >= 0)
			conv->precision = (free(conv->precision), ft_itoa(tmp));
		else
			conv->precision = (free(conv->precision), NULL);
	}
}

static void	get_prec_n_width(t_conv_details *det, t_conv *conv)
{
	det->min_width = ft_atoi(conv->width);
	det->precision = ft_atoi(conv->precision);
	det->len = ft_min(det->min_width, det->precision);
	if (!det->precision)
	{
		if (!contains("dixXs", conv->type))
			det->precision = det->min_width;
		det->is_zeroed = 1;
	}
	if ('s' != conv->type)
		det->len = ft_max(det->min_width, det->precision);
	if ('%' == conv->type)
		det->len = det->min_width;
	det->is_precisioned = 1;
}

t_conv_details	*conv_handler(t_conv *conv, va_list ap)
{
	t_conv_details	*det;

	width_n_prec_from_args(conv, ap);
	det = create_det_n_set_flags(conv);
	if (!det)
		return (NULL);
	if ((!(conv->width) && !(conv->precision)))
		det->len = 0;
	else if (!(conv->width))
		get_prec(det, conv);
	else if (!(conv->precision) || 'c' == conv->type)
	{
		det->len = ft_atoi(conv->width);
		det->min_width = det->len;
		if (conv->type == 'd' || conv->type == 'i')
			det->len = 0;
	}
	else if (contains("diuxXp%s", conv->type))
		get_prec_n_width(det, conv);
	return (det);
}
