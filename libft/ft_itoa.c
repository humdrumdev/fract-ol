/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:06:50 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/03 19:00:12 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static long	ft_negornul(char *str, int n, int *size)
{
	if (n <= 0)
	{
		if (n)
			*str = '-';
		else
			*str = '0';
		(*size)++;
		return (-(long)n);
	}
	return (n);
}

static void	ft_strrev(char *str, int size)
{
	int		i;
	char	tmp;

	i = -1;
	while (++i < (size / 2))
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
	}
}

static int	num_len(int num)
{
	int	len;

	len = 0;
	if (num == (1 << 31))
		return (12);
	if (len <= 0)
	{
		len++;
		num = -num;
	}
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	char		*num;
	long		nb;
	int			size;

	num = (char *)malloc(num_len(n) * sizeof(char));
	if (!num)
		return (NULL);
	size = 0;
	nb = ft_negornul(num, n, &size);
	while (nb)
	{
		num[size++] = (nb % 10) + '0';
		nb /= 10;
	}
	num[size] = '\0';
	if (n)
		ft_strrev(num + (n < 0), size - (n < 0));
	return (num);
}
