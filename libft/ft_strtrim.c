/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:54:32 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/02 16:55:11 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static inline size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static inline int	ft_isinset(const char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	len;
	char	*new;

	new = NULL;
	if (s && set)
	{
		len = ft_strlen(s);
		while (len && ft_isinset(s[len - 1], set))
			len--;
		while (len && ft_isinset(*s, set))
		{
			s++;
			len--;
		}
		new = malloc((len + 1) * sizeof(char));
		if (new)
		{
			new[len] = 0;
			while (len--)
				new[len] = s[len];
		}
	}
	return (new);
}
