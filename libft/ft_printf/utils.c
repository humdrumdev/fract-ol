/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:22:27 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:46:54 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	init_conv_details(t_conv_details *det)
{
	det->is_zero_padded = 0;
	det->is_hash_padded = 0;
	det->is_sign_padded = 0;
	det->is_space_padded = 0;
	det->is_padded_to_left = 0;
	det->is_padded_to_right = 0;
	det->is_precisioned = 0;
	det->precision = 0;
	det->min_width = 0;
	det->is_zeroed = 0;
	det->has_blank = 0;
}

int	contains(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	num_size(unsigned int nbr, int base_len)
{
	int		size;

	size = 1;
	while (nbr / base_len)
	{
		size++;
		nbr /= base_len;
	}
	return (size);
}
