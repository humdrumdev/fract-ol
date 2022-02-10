/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:26:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/10 15:00:12 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	usage(char *s)
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

static t_mlx *new_mlx(int im_width, int im_height, char *title)
{
	t_mlx *new;

	new = NULL;
	if (free_alloc((void **)&new, sizeof(t_mlx)))
		return (NULL);
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
		return (free(new), NULL);
	new->win_ptr = mlx_new_window(new->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!new->win_ptr)
		return (free(new->mlx_ptr), free(new), NULL);
	new->addr = init_image(new, &new->im_ptr, im_width, im_height);
	if (!new->addr)
	{
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free(new), NULL);
	}
	new->tmp_addr = init_image(new, &new->tmp_im_ptr, im_width, im_height);
	if (!new->tmp_addr)
	{
		mlx_destroy_image(new->mlx_ptr, new->im_ptr);
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free(new), NULL);
	}
	return (new);
}

static int	init_mlx_data(t_mlx *mlx)
{
	if (free_alloc((void **)&mlx->bounds, sizeof(t_bounds)))
		return (-1);
	if (free_alloc((void **)&mlx->draw, sizeof(t_draw)))
		return (free_alloc(NULL, 0), -1);
	mlx->bounds->re_max = 2.;
	mlx->bounds->re_min = -2.;
	mlx->bounds->im_max = 2.;
	mlx->bounds->im_min = -2.;
	mlx->bounds->d_r = 4.;
	mlx->bounds->d_i = 4.;
	mlx->draw->img = NULL;
	mlx->draw->draw = NULL;
	mlx->coloriser = NULL;
	mlx->color_gen = INV_LOG2;
	mlx->im_height = SIZE_Y;
	mlx->im_width = SIZE_X;
	mlx->j = -0.25;
	mlx->k = 0.;
	mlx->s_height = SIZE_Y;
	mlx->s_width = SIZE_X;
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2 || !valid_name(av[1]))
		usage(av[0]);
	mlx = new_mlx(SIZE_X, SIZE_Y, av[1]);
	if (!mlx || init_mlx_data(mlx))
		exit((ft_printf("Error in initialization!\n"), EXIT_FAILURE));
	return (0);
}
