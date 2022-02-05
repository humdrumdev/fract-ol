/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:58:17 by hel-moud          #+#    #+#             */
/*   Updated: 2021/12/18 20:54:39 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"

int	handle_hash(char type, t_conv_details *det)
{
	if (type == 'x' || type == 'X')
	{
		det->is_hash_padded = 1;
		return (0);
	}
	if (type == '%')
		return (0);
	return (-1);
}

int	handle_zero(char type, t_conv_details *det)
{
	if ((type == 'x' || type == 'X') && det->is_padded_to_left)
		return (-1);
	if ((type == 'd' || type == 'i') && det->is_padded_to_left)
		return (-1);
	if (type == 'c' || type == 'p')
		return (-1);
	if (type)
	{
		det->is_zero_padded = 1;
		det->is_padded_to_right = 1;
		if (type == 's' && det->is_space_padded)
			det->is_padded_to_right = 0;
	}
	return (0);
}

int	handle_minus(char type, t_conv_details *det)
{
	if ((type == 'x' || type == 'X') && det->is_zero_padded)
		return (-1);
	if ((type == 'i' || type == 'd') && det->is_zero_padded)
		return (-1);
	if (type)
	{
		det->is_padded_to_left = 1;
		det->is_space_padded = 1;
		if (det->is_padded_to_right)
			det->is_padded_to_right = 0;
		if (det->is_zero_padded)
			det->is_zero_padded = 0;
	}
	return (0);
}

int	handle_space(char type, t_conv_details *det)
{
	if (type == 'c')
		return (-1);
	if (type == 'd' || type == 'i' || type == '%' || type == 's')
	{
		if ((type == 'd' || type == 'i') && det->is_sign_padded)
			return (-1);
		det->is_padded_to_right = 1;
		det->is_space_padded = 1;
		det->has_blank = 1;
		return (0);
	}
	return (-1);
}

int	handle_plus(char type, t_conv_details *det)
{
	if (type == 'd' || type == 'i')
	{
		if (det->is_space_padded && det->has_blank)
			return (-1);
		det->is_sign_padded = 1;
		det->is_padded_to_right = 1;
		if (det->is_space_padded)
			det->is_space_padded = 0;
		return (0);
	}
	if (type == '%')
		return (0);
	return (-1);
}
