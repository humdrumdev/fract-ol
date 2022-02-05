/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:03:30 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 12:42:48 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (dst[i] && size)
	{
		i++;
		size--;
	}
	while (*src && size > 1)
	{
		dst[i++] = *src;
		src++;
		size--;
	}
	if (size)
		dst[i] = '\0';
	while (*src++)
		i++;
	return (i);
}
