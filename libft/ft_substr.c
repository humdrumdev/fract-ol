/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:49:13 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 11:49:08 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

static void	*ft_clc(size_t count, size_t size)
{
	void	*new;
	size_t	i;

	i = 0;
	new = NULL;
	if (count && size)
		new = malloc(count * size);
	if (new)
		while (i++ < count * size)
			*((char *)new + i - 1) = 0;
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;
	unsigned int	slen;

	slen = ft_strlen(s);
	if (s)
	{
		if (start > slen)
			start = slen;
		if (len > slen)
			len = slen - start;
		new = (char *)ft_clc(len + 1, sizeof(char));
		if (new)
		{
			i = 0;
			while ((i < len) && s[start + i])
			{
				new[i] = s[start + i];
				i++;
			}
			return (new);
		}
	}
	return (NULL);
}
