/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:46:27 by hel-moud          #+#    #+#             */
/*   Updated: 2022/03/16 18:19:04 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	usage(char *s)
{
	ft_printf(BIN_USAGE, s);
	ft_printf(BIN_USAGE2);
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

static inline int	valid_args(char **av, int ac, t_args *args)
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

static inline void	init_default_constraints(t_mlx *mlx, t_args *args)
{
	mlx->args = args;
	mlx->px_move = 20;
	mlx->n_max = 30;
	mlx->radius_sq = 4;
	mlx->coloriser = get_color;
	mlx->color_gen = INV_LOG2 * 100;
}

// static inline void	*free_d_tab(double **tab)
// {
// 	int	i;

// 	i = -1;
// 	while (tab[++i])
// 		free(tab[i]);
// 	free(tab);
// 	return (NULL);
// }

// static inline void	init_d_tab(double **tab)
// {
// 	tab[0][0] = 0.3;
// 	tab[0][1] = 0.5;

// 	tab[1][0] = 0.285;
// 	tab[1][1] = 0.01;

// 	tab[2][0] = -1.417022285618;
// 	tab[2][1] = 0.0099534;

// 	tab[3][0] = -0.038088;
// 	tab[3][1] = 0.9754633;

// 	tab[4][0] = 0.285;
// 	tab[4][1] = 0.013;

// 	tab[5][0] = 0.285;
// 	tab[5][1] = 0.01;

// 	tab[6][0] = -1.476;
// 	tab[6][1] = 0.;

// 	tab[7][0] = -0.4;
// 	tab[7][1] = 0.6;

// 	tab[8][0] = -0.8;
// 	tab[8][1] = 0.156;
// }

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	t_args	args;

	args.set = 0;
	args.w_dist = false;
	args.w_shades = false;
	args.toggle_coloriser = false;
	if ((ac == 1 || ac > 5) || !valid_args(av, ac, &args))
		usage(av[0]);
	mlx = new_mlx(SIZE_X, SIZE_Y, av[1]);
	if (!mlx || init_mlx_data(mlx))
		exit((ft_printf(INIT_ERROR), EXIT_FAILURE));
	init_default_constraints(mlx, &args);
	mlx->draw->draw = draw;
	mlx->collection = false;
	init_listners(mlx);
	put_next_frame(mlx);
	show_use(mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
