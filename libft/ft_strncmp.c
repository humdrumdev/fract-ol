/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:24:08 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/01 14:41:39 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *lhs, const char *rhs, size_t count)
{
	if (!count)
		return (0);
	while (*lhs && count > 1)
	{
		if (*lhs != *rhs)
			break ;
		lhs++;
		rhs++;
		count--;
	}
	return (*(const unsigned char *)lhs - *(const unsigned char *)rhs);
}
