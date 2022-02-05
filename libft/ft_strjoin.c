/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:51:33 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/02 16:49:21 by hel-moud         ###   ########.fr       */
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

char	*ft_strjoin(const char *lhs, const char *rhs)
{
	char	*new;
	int		i;
	int		lhs_len;

	if (lhs && rhs)
	{
		new = malloc((ft_strlen(lhs) + ft_strlen(rhs) + 1) * sizeof(char));
		if (new)
		{
			i = -1;
			while (lhs[++i])
				new[i] = lhs[i];
			lhs_len = i;
			i = -1;
			while (rhs[++i])
				new[lhs_len + i] = rhs[i];
			new[lhs_len + i] = 0;
			return (new);
		}
	}
	return (NULL);
}
