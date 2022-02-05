/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:25:13 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 16:17:41 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "lst.h"

void	init_conv_details(t_conv_details *det);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		contains(const char *s, const char c);
int		num_size(unsigned int nbr, int base_len);
int		ft_putnbr_base(unsigned int nbr, char *base, unsigned int base_len);
int		ft_putint_base(int nbr, char *base, unsigned int base_len);
int		put_longnum_base_fd(int fd, unsigned long n, char *b, unsigned long l);
int		long_size(unsigned long nbr, unsigned long base_len);
int		get_absv(int *num);

#endif
