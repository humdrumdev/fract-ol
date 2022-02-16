/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:11:40 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/17 00:31:02 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// get_color((double)n / NMAX);
// (n == NMAX) ? 0 : get_color(sin(n));
// get_periodic_color(v);
// n == NMAX ? 0 : get_periodic_color(v);
// d < line_width ? 0 : get_color((double)n / NMAX);
// d < line_width ? 0 : 0x00FFFFFF;
// (d < line_width || n == NMAX) ? 0 : get_periodic_color(sin(v));

int	get_periodic_color(double t)
{
	double	r;
	double	g;
	double	b;

	r = (1. - cos(A * t)) * 127.5;
	g = (1. - cos(B * t)) * 127.5;
	b = (1. - cos(C * t)) * 127.5;
	return ((int)floor(r) << 16 | (int)floor(g) << 8 | (int)floor(b));
}

int	get_color(double t)
{
	double	r;
	double	g;
	double	b;

	assert(t <= 1. && t >= 0.);
	r = BERNSTEIN1 * (1. - t) * pow(t, 2.);
	g = BERNSTEIN2 * pow(1. - t, 2.) * pow(t, 2.);
	b = BERNSTEIN3 * pow(1. - t, 3.) * t;
	return ((int)floor(r) << 16 | (int)floor(g) << 8 | (int)floor(b));
}

int	colorize(t_mlx *mlx, t_draw *vars)
{
	double	t;

	if (mlx->args->w_shades)
	{
		mlx->draw->v *= mlx->color_gen;
		t = mlx->draw->v;
		mlx->coloriser = get_periodic_color;
	}
	else
		t = ((double)vars->n) / mlx->n_max;
	return (mlx->coloriser(t));
}
