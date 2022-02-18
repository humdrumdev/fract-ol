/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:11:40 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 17:53:47 by hel-moud         ###   ########.fr       */
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
	else if (!mlx->args->w_shades && mlx->args->w_dist)
	{
		t = ((double)vars->n) / mlx->n_max;
		t = (1. - cos (t * mlx->color_gen)) / 2.;
		mlx->coloriser = get_color;
	}
	else
	{
		t = ((double)vars->n) / mlx->n_max;
		t = (1. - sin(t * mlx->color_gen)) / 2.;
	}
	return (mlx->coloriser(t));
}
