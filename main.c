/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:26:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/11 19:41:08 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	usage(char *s)
{
	ft_printf("usage : %s <fractal name>\n", s);
	ft_printf("fractals :\n");
	ft_printf("\t\t-> mandelbrot\n");
	ft_printf("\t\t-> julia\n");
	ft_printf("\t\t-> mandelbrot\n");
	exit(EXIT_FAILURE);
}

static int	valid_name(char *s, int *set)
{
	if (ft_strcmp(s, "mandelbrot"))
	{
		if (ft_strcmp(s, "julia"))
		{
			if (ft_strcmp(s, "mandelbrot2"))
				return (0);
			*set = MANDELBROT2;
		}
		else
			*set = JULIA;
	}
	else
		*set = MANDELBROT;
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

static inline void	init_draw_func(int set, t_mlx *mlx)
{
	if (set == MANDELBROT)
		mlx->draw->draw = &mandelbrot;
	if (set == JULIA)
		mlx->draw->draw = &julia;
	else
		mlx->draw->draw = &mandelbrot2;
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
	mlx->coloriser = NULL;
	mlx->color_gen = INV_LOG2;
	mlx->im_height = SIZE_Y;
	mlx->im_width = SIZE_X;
	mlx->j = -0.8;
	mlx->k = 0.156;
	// c = −0.8 + 0.156i
	mlx->s_height = SIZE_Y;
	mlx->s_width = SIZE_X;
	return (0);
}

/*
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
*/

// get_color((double)n / NMAX);
// (n == NMAX) ? 0 : get_color(sin(n));
// get_periodic_color(v);
// n == NMAX ? 0 : get_periodic_color(v);
// d < line_width ? 0 : get_color((double)n / NMAX);
// d < line_width ? 0 : 0x00FFFFFF;
// (d < line_width || n == NMAX) ? 0 : get_periodic_color(sin(v));

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	char	*img;
	int		set;

	set = 0;
	if (ac != 2 || !valid_name(av[1], &set))
		usage(av[0]);
	mlx = new_mlx(SIZE_X, SIZE_Y, av[1]);
	if (!mlx || init_mlx_data(mlx))
		exit((ft_printf("Error in initialization!\n"), EXIT_FAILURE));
	init_draw_func(set, mlx);
	signal(SIGINT, interupt_handler);
	img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
	ft_memcpy(mlx->addr, img, SIZE_X * SIZE_Y * 4 + 1);
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, handle_mouse, mlx);
	// mlx_hook(mlx->win_ptr, ON_MOUSEMOVE, 0, change_julia, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}