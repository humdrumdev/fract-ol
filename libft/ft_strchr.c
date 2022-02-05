/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:18:35 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 12:41:43 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	char	*result;

	ch = (char)c;
	result = NULL;
	while (*s && ((char)(*s) != ch))
		s++;
	if ((char)(*s) == ch)
		result = (char *)s;
	return (result);
}
