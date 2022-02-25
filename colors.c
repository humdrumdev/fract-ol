/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:11:40 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/25 22:01:41 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	double	tmp;
	double	tmp2;

	tmp = 1. - t;
	tmp2 = tmp * tmp;
	r = BERNSTEIN1 * tmp * pow(t, 3.);
	g = BERNSTEIN2 * tmp2 * pow(t, 2.);
	b = BERNSTEIN3 * tmp * tmp2 * t;
	return ((int)floor(r) << 16 | (int)floor(g) << 8 | (int)floor(b));
}

int	colorize(t_mlx *mlx, t_draw *vars)
{
	double	t;

	if (mlx->args->w_shades)
	{
		mlx->draw->v *= mlx->color_gen;
		t = mlx->draw->v;
	}
	else if (!mlx->args->w_shades && mlx->args->w_dist)
	{
		t = ((double)vars->n) / mlx->n_max;
		t = (1. - cos (t * mlx->color_gen)) / 2.;
	}
	else
	{
		t = ((double)vars->n) / mlx->n_max;
		t = (1. - sin(t * mlx->color_gen)) / 2.;
	}
	if (!mlx->args->toggle_coloriser)
		mlx->coloriser = get_periodic_color;
	else
		mlx->coloriser = get_color;
	return (mlx->coloriser(t));
}
