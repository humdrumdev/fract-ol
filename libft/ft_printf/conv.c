/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:34:23 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 19:28:07 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_putnbr_base(unsigned int nbr, char *base, unsigned int base_len)
{
	int	len;

	len = 0;
	if (nbr < base_len)
		return (write(1, &base[nbr], 1));
	else
	{
		len += ft_putnbr_base((nbr / base_len), base, base_len);
		len += write(1, &base[nbr % base_len], 1);
	}
	return (len);
}

int	ft_putint_base(int nbr, char *base, unsigned int base_len)
{
	int	len;

	len = 0;
	if (nbr >= 0)
		return (ft_putnbr_base(nbr, base, base_len));
	len += write(1, "-", 1);
	len += ft_putnbr_base(-nbr, base, base_len);
	return (len);
}

int	put_longnum_base_fd(int fd, unsigned long n, char *b, unsigned long len)
{
	int	size;

	size = 0;
	if (n < len)
		return (write(fd, &b[n], 1));
	else
	{
		size = put_longnum_base_fd(fd, n / len, b, len);
		return (size + write(fd, &b[n % len], 1));
	}
}

int	long_size(unsigned long nbr, unsigned long base_len)
{
	int	size;

	size = 1;
	if (nbr == 0)
		return (1);
	while (nbr / base_len)
	{
		size++;
		nbr /= base_len;
	}
	return (size);
}

int	get_absv(int *num)
{
	if (*num < 0)
		*num *= -1;
	return (1);
}
