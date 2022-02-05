/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:05:03 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 12:43:06 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	if (!(*needle))
		return ((char *)haystack);
	while (*haystack && len--)
	{
		i = 0;
		l = len;
		while (*(needle + i) && *(needle + i) == *(haystack + i))
		{
			i++;
			if (!l && needle[i])
				return (NULL);
			l--;
		}
		if (!needle[i])
			return ((char *)(haystack));
		haystack++;
	}
	return (NULL);
}
