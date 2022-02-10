/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:26:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/10 11:46:54 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	usage(char *s)
{
	ft_printf("usage : %s <fractal name>\n");
	ft_printf("fractals :\n");
	ft_printf("\t\t-> mandelbrot\n");
	ft_printf("\t\t-> julia\n");
	ft_printf("\t\t-> mandelbrot\n");
	exit(EXIT_FAILURE);
}

static int	valid_name(char *s)
{
	if (ft_strcmp(s, "mandelbrot"))
		if (ft_strcmp(s, "julia"))
			if (ft_strcmp(s, "mandelbrot"))
				return (0);
	return (1);
}

static int	init_mlx(t_mlx *mlx)
{
	
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2 || !valid_name(av[1]))
		usage(av[0]);
	
		
}