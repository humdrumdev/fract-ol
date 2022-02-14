/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:06:53 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/14 18:24:54 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	initial_values(t_draw *vars, t_bounds *bounds, int set, t_mlx *mlx)
{
	if (set != JULIA)
	{
		vars->r_c = bounds->re_min + (vars->x * vars->px_size);
		vars->i_c = bounds->im_max - (vars->y * vars->px_size);
		vars->r_z = 0.;
		vars->i_z = 0.;
		vars->r_zp = 0.;
		vars->i_zp = 0.;
	}
	else
	{
		vars->r_c = mlx->j;
		vars->i_c = mlx->k;
		vars->r_z = bounds->re_min + (vars->x * vars->px_size);
		vars->i_z = bounds->im_max - (vars->y * vars->px_size);
		vars->r_zp = 1.;
		vars->i_zp = 0.;
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
			vars->n = mlx->n_max;
	}
}

static void	compute_next(t_draw *vars, int set)
{
	double	a;
	double	b;
	double	c;
	double	d;

	if (set == DOUBLEBROT)
	{
		vars->tmp = vars->i_z;
		vars->tmp_p = vars->r_zp;
		a = vars->r_z * vars->r_z;
		b = vars->i_z * vars->i_z;
		c = vars->i_z * vars->r_z;
		d = (a * vars->r_zp - vars->r_zp * b - (c + c) * vars->i_zp);
		vars->r_zp = 1. + d + d + d;
		vars->i_zp = (- vars->i_zp * b + vars->i_zp * a + (c + c) * vars->tmp_p);
		vars->i_zp += vars->i_zp + vars->i_zp;
		vars->i_z = (a + a + a - b) * vars->i_z + vars->i_c;
		vars->r_z = (a - (b + b + b)) * vars->r_z + vars->r_c;
	}
	else
	{
		vars->tmp = vars->i_z;
		a = vars->r_z * vars->r_z;
		b = vars->i_z * vars->i_z;
		c = vars->i_z * vars->r_z;
		d = vars->r_z * vars->r_zp;
		vars->tmp = vars->i_z * vars->i_zp;
		vars->tmp_p = vars->r_zp;
		vars->r_zp = (set == MANDELBROT) + (d + d - (vars->tmp + vars->tmp));
		vars->tmp = vars->r_z * vars->i_zp;
		vars->tmp_p *= vars->i_z;
		vars->i_zp = (vars->tmp + vars->tmp_p + vars->tmp + vars->tmp_p);
		vars->i_z = c + c + vars->i_c;
		vars->r_z = a - b + vars->r_c;
	}
	vars->powr += vars->powr;
	vars->n++;
}

static inline void	compute_distance(t_draw *vars, int n_max)
{
	vars->v = log(vars->tmp) / vars->powr;
	vars->v = log(vars->v);
	if (vars->n == n_max)
		vars->d = 0.;
	else
	{
		vars->tmp = vars->r_z * vars->r_z + vars->i_z * vars->i_z;
		vars->tmp_p = vars->r_zp * vars->r_zp + vars->i_zp * vars->i_zp;
		vars->tmp_p = vars->tmp / vars->tmp_p;
		vars->d = sqrt(vars->tmp_p) * log(vars->tmp);
	}
}

void	colorise_pixel(t_mlx *mlx, t_draw *vars)
{
	int	*position;

	reset_vars(vars, mlx->bounds, mlx->set, mlx);
	while (vars->n < mlx->n_max)
	{
		vars->tmp = (vars->r_z * vars->r_z) + (vars->i_z * vars->i_z);
		if (vars->tmp > mlx->radius_sq)
			break ;
		compute_next(vars, mlx->set);
	}
	compute_distance(vars, mlx->n_max);
	position = (int *)(vars->img + vars->y * mlx->line_size + 4 * vars->x);
	if (vars->d < vars->line_width || vars->n == mlx->n_max)
		*position = 0;
	else
		*position = colorize(mlx, vars);
}