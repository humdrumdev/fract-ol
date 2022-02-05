/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:17:19 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/01 14:18:22 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *lhs, const void *rhs, size_t count)
{
	unsigned char	*l;
	unsigned char	*r;

	l = (unsigned char *)lhs;
	r = (unsigned char *)rhs;
	while (count--)
	{
		if (*l != *r)
			return (*l - *r);
		l++;
		r++;
	}
	return (0);
}
