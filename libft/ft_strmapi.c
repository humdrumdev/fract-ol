/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:11:51 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/02 17:05:32 by hel-moud         ###   ########.fr       */
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

char	*ft_strmapi(char const *s, char (*func)(unsigned int, char))
{
	int		i;
	char	*new;

	if (s && func)
	{
		new = malloc((ft_strlen(s) + 1) * sizeof(char));
		if (new)
		{
			i = -1;
			while (s[++i])
				new[i] = (*func)(i, s[i]);
			new[i] = 0;
			return (new);
		}
	}
	return (NULL);
}
