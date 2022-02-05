/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:59:37 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 14:00:06 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	if (!n)
		return (dest);
	if (!dest && !src)
		return (NULL);
	pd = dest;
	ps = src;
	if (ps < pd)
	{
		pd += n - 1;
		ps += n - 1;
		while (n--)
			*pd-- = *ps--;
	}
	else
		while (n--)
			*pd++ = *ps++;
	return (dest);
}
