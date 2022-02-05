/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:48:07 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 12:42:33 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;

	srclen = 0;
	while (*(src + srclen) && (size > 1))
	{
		if (srclen == size - 1)
			break ;
		*(dest + srclen) = *(src + srclen);
		srclen++;
	}
	if (size > 0)
		*(dest + srclen) = '\0';
	while (*(src + srclen))
	{
		srclen++;
	}
	return (srclen);
}
