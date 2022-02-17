/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:26:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/17 18:54:40 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <assert.h>

static inline void	usage(char *s)
{
	ft_printf("usage : %s <fractal name> [optional : enhanced (-e)] [optional: gradient coloring (-c)]\n", s);
	ft_printf("fractals :\n");
	ft_printf("\t\t-> mandelbrot\n");
	ft_printf("\t\t-> julia\n");
	ft_printf("\t\t-> doublebrot\n");
	exit(EXIT_FAILURE);
}

static int	valid_name(char *s, t_args *args)
{
	if (ft_strcmp(s, "doublebrot"))
	{
		if (ft_strcmp(s, "julia"))
		{
			if (ft_strcmp(s, "mandelbrot"))
				return (0);
			args->set = MANDELBROT;
		}
		else
			args->set = JULIA;
	}
	else
		args->set = DOUBLEBROT;
	return (1);
}

static int	valid_args(char **av, int ac, t_args *args)
{
	if (!valid_name(av[1], args))
		return (0);
	if (ac > 2)
	{
		if (ac == 4)
			args->w_shades = true;
		args->w_dist = true;
	}
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
		return (free_alloc(NULL, 0), NULL);
	new->win_ptr = mlx_new_window(new->mlx_ptr, im_width, im_height, title);
	if (!new->win_ptr)
		return (free(new->mlx_ptr), free_alloc(NULL, 0), NULL);
	new->addr = init_image(new, &new->im_ptr, im_width, im_height);
	if (!new->addr)
	{
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free_alloc(NULL, 0), NULL);
	}
	new->tmp_addr = init_image(new, &new->tmp_im_ptr, im_width, im_height);
	if (!new->tmp_addr)
	{
		mlx_destroy_image(new->mlx_ptr, new->im_ptr);
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free_alloc(NULL, 0), NULL);
	}
	return (new);
}

static int	init_mlx_data(t_mlx *mlx)
{
	if (free_alloc((void **)&mlx->bounds, sizeof(t_bounds)))
		return (-1);
	if (free_alloc((void **)&mlx->def_bounds, sizeof(t_bounds)))
		return (free_alloc(NULL, 0), -1);
	if (free_alloc((void **)&mlx->draw, sizeof(t_draw)))
		return (free_alloc(NULL, 0), -1);
	mlx->bounds->re_max = 2.;
	mlx->bounds->re_min = -2.;
	mlx->bounds->im_max = 2.;
	mlx->bounds->im_min = -2.;
	mlx->bounds->d_r = 4.;
	mlx->bounds->d_i = 4.;
	ft_memcpy(mlx->def_bounds, mlx->bounds, sizeof(t_bounds));
	mlx->draw->img = NULL;
	mlx->coloriser = NULL;
	mlx->color_gen = INV_LOG2;
	mlx->im_height = 1000;
	mlx->im_width = 1000;
	mlx->j = -0.8;
	mlx->k = 0.156;
	mlx->def_j = -0.8;
	mlx->def_k = 0.156;
	mlx->event = 0;
	return (0);
}

void	swap_vp(void **a, void **b)
{
	void	*t;

	t = *a;
	*a = *b;
	*b = t;
}

void	put_next_frame(t_mlx *mlx)
{
	mlx->draw->draw(mlx);
	swap_vp((void **)&mlx->addr, (void **)&mlx->tmp_addr);
	swap_vp((void **)&mlx->im_ptr, (void **)&mlx->tmp_im_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	//think about it
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 0, 0, 0x00FF0000, "hello");
}

void	init_default_constraints(t_mlx *mlx, t_args *args)
{
	mlx->args = args;
	mlx->px_move = 20; // no need to change
	mlx->n_max = 30; // can be modified
	mlx->radius_sq = 4; // start with 4 and keep going up
	mlx->coloriser = get_color; // the default, can be changesd from command line
	mlx->color_gen = INV_LOG2 * 100; // needs to get smaller with time
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	t_args	args;

	args.set = 0;
	args.w_dist = false;
	args.w_shades = false;
	if ((ac == 1 || ac > 5) || !valid_args(av, ac, &args))
		usage(av[0]);
	mlx = new_mlx(1000, 1000, av[1]);
	if (!mlx || init_mlx_data(mlx))
		exit((ft_printf("Error in initialization!\n"), EXIT_FAILURE));
	// init constraints
	init_default_constraints(mlx, &args);
	mlx->draw->draw = draw;
	//set up event listeners
	init_listners(mlx);

	// draw image and swap
	put_next_frame(mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
