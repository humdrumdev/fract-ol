/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:54:37 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:43:57 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"
#include "lst.h"

int	handle_flag(char flag, char type, t_conv_details *det)
{
	if (flag == '#')
		return (handle_hash(type, det));
	if (flag == '0')
		return (handle_zero(type, det));
	if (flag == '-')
		return (handle_minus(type, det));
	if (flag == ' ')
		return (handle_space(type, det));
	if (flag == '+')
		return (handle_plus(type, det));
	return (1);
}

int	flag_handler(char type, char *flags, t_conv_details *det)
{
	int	i;

	if (!flags)
		return (0);
	i = 0;
	while (flags[i])
		if (handle_flag(flags[i++], type, det) == -1)
			return (-1);
	return (0);
}
