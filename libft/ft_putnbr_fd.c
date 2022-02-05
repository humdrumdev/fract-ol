/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:19:51 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 15:56:19 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	c;
	int		len;

	len = 0;
	if (fd < 0)
		return (-1);
	num = n;
	if (n <= 0)
	{
		if (!n)
		{
			len += write(fd, "0", 1);
			return (len);
		}
		len += write(fd, "-", 1);
		num *= -1;
	}
	if (num >= 10)
		len += ft_putnbr_fd(num / 10, fd);
	c = (num % 10) + '0';
	return (len + write(fd, &c, 1));
}
