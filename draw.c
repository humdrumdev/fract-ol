/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:06:53 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 18:02:52 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	initial_values(t_draw *vars, 
									t_bounds *bounds, int set, t_mlx *mlx)
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

static void	reset_vars(t_draw *vars, t_bounds *bounds, t_mlx *mlx)
{
	double	tmp1;
	double	tmp2;
	double	tmp3;

	initial_values(vars, bounds, mlx->args->set, mlx);
	vars->n = 0;
	vars->powr = 1.;
	if (mlx->args->set == MANDELBROT)
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

static inline void	compute_next(t_mlx *mlx, t_draw *vars)
{
	if (mlx->args->set == DOUBLEBROT)
		vars->tmp = compute_next_doublebrot(mlx, vars);
	else
		vars->tmp = compute_next_fract(mlx, vars);
	vars->powr += vars->powr;
	vars->n++;
}

static inline void	compute_distance(t_draw *vars, int n_max, int with_shades)
{
	if (vars->n == n_max)
		vars->d = 0.;
	else
	{
		vars->tmp = vars->r_z * vars->r_z + vars->i_z * vars->i_z;
		vars->tmp_p = vars->r_zp * vars->r_zp + vars->i_zp * vars->i_zp;
		vars->tmp_p = vars->tmp / vars->tmp_p;
		vars->d = sqrt(vars->tmp_p) * log(vars->tmp);
	}
	if (with_shades)
	{
		if (vars->tmp < 1.)
			vars->v = 0.;
		else
		{
			vars->v = log(vars->tmp) / vars->powr;
			vars->v = log(vars->v);
		}
	}
}

void	colorise_pixel(t_mlx *mlx, t_draw *vars)
{
	int	*position;

	reset_vars(vars, mlx->bounds, mlx);
	vars->tmp = 0;
	while (vars->n < mlx->n_max)
	{
		if (vars->tmp > mlx->radius_sq)
			break ;
		compute_next(mlx, vars);
	}
	position = (int *)(vars->img + vars->y * mlx->line_size + 4 * vars->x);
	*position = 1;
	if (mlx->args->w_dist)
	{
		compute_distance(vars, mlx->n_max, mlx->args->w_shades);
		if (vars->d < vars->line_width)
			*position = 0;
	}
	if (vars->n == mlx->n_max)
		*position = 0;
	if (*position)
		*position = colorize(mlx, vars);
}