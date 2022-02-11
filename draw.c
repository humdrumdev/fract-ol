/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:06:53 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/11 17:05:56 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*mandelbrot(t_mlx *mlx, t_color coloriser, double color_gen);
char	*julia(t_mlx *mlx, t_color coloriser, double color_gen);
char	*other(t_mlx *mlx, t_color coloriser, double color_gen);

static inline void	initial_values(t_draw *vars, t_bounds *bounds, int set, t_mlx *mlx)
{
	if (set == MANDELBROT)
	{
		vars->r_c = bounds->re_min + (vars->x * vars->px_size);
		vars->i_c = bounds->im_max - (vars->y * vars->px_size);
		vars->r_z = 0;
		vars->i_z = 0;
		vars->r_zp = 0;
		vars->i_zp = 0;
	}
	if (set == JULIA)
	{
		vars->r_c = bounds->re_min + (mlx->j * vars->px_size);
		vars->i_c = bounds->im_max - (mlx->k * vars->px_size);
		// vars->r_c = mlx->j;
		// vars->i_c = mlx->k;
		vars->r_z = bounds->re_min + (vars->x * vars->px_size);
		vars->i_z = bounds->im_max - (vars->y * vars->px_size);
		vars->r_zp = 1.;
		vars->i_zp = 0;
	}
}

static void	reset_vars(t_draw *vars, t_bounds *bounds, int set, t_mlx *mlx)
{
	double	tmp1;
	double	tmp2;
	double	tmp3;

	initial_values(vars, bounds, set, mlx);
	vars->n = 0;
	vars->powr = 1.;
	if (set == MANDELBROT)
	{
		vars->q = pow(vars->r_c - 0.25, 2.) + vars->i_c * vars->i_c;
		tmp1 = vars->q * (vars->q + vars->r_c - 0.25);
		tmp2 = vars->i_c * vars->i_c * 0.25;
		tmp3 = vars->r_c * vars->r_c + vars->r_c + vars->r_c + 1;
		tmp3 += vars->i_c * vars->i_c;
		if (tmp1 < tmp2 || tmp3 < 0.0625)
			vars->n = NMAX;
	}
}

static void	compute_next(t_draw *vars, int set)
{
	vars->tmp = vars->i_z;
	vars->tmp_p = vars->r_zp;
	vars->r_zp = (set == MANDELBROT) + 2 * (vars->r_z * vars->r_zp - vars->i_z * vars->i_zp);
	vars->i_zp = 2 * (vars->r_z * vars->i_zp + vars->i_z * vars->tmp_p);
	vars->i_z = (vars->i_z + vars->i_z) * vars->r_z + vars->i_c;
	vars->r_z = vars->r_z * vars->r_z - vars->tmp * vars->tmp + vars->r_c;
	vars->powr += vars->powr;
	vars->n++;
}

static void	compute_distance(t_draw *vars, double color_gen)
{
	vars->v = log(vars->tmp) / vars->powr;
	vars->v = log(vars->v) * color_gen;
	if (vars->n == NMAX)
		vars->d = 0;
	else
	{
		vars->tmp = vars->r_z * vars->r_z + vars->i_z * vars->i_z;
		vars->tmp_p = vars->r_zp * vars->r_zp + vars->i_zp * vars->i_zp;
		vars->d = (sqrt(vars->tmp) * log(vars->tmp) / sqrt(vars->tmp_p));
	}
}

void	colorise_pixel(t_mlx *mlx, t_draw *vars, t_color coloriser, double color_gen)
{
	int	*position;

	reset_vars(vars, mlx->bounds, mlx->set, mlx);
	while (vars->n < NMAX)
	{
		vars->tmp = (vars->r_z * vars->r_z) + (vars->i_z * vars->i_z);
		if (vars->tmp > RADIUS2)
			break ;
		compute_next(vars, mlx->set);
	}
	compute_distance(vars, color_gen);
	position = (int *)(vars->img + vars->y * mlx->line_size + 4 * vars->x);
	if (vars->d < vars->line_width || vars->n == NMAX)
		*position = 0;
	else
		*position = coloriser(vars->v);
	vars->x++;
}