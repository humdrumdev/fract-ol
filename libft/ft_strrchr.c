/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:14:55 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 12:42:03 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static inline int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*result;

	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	ch = (char)c;
	result = NULL;
	while (*s)
	{
		if ((char)(*s) == ch)
			result = (char *)s;
		s++;
	}
	return (result);
}
