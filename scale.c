/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:12:44 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/10 15:21:06 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scale(t_bounds *bounds, int direction, double x, double y)
{
	double	x_ratio;
	double	y_ratio;
	double	scale_factor;
	double	ddre;
	double	ddim;

	x_ratio = x / SIZE_X;
	y_ratio = y / SIZE_Y;
	if (direction == 1)
		scale_factor = 0.8;
	else
		scale_factor = 2.;
	ddre = (scale_factor * bounds->d_r) - bounds->d_r;
	ddim = (scale_factor * bounds->d_i) - bounds->d_i;
	bounds->re_max += ddre * (1. - x_ratio);
	bounds->re_min += -ddre * x_ratio;
	bounds->im_max += ddim * y_ratio;
	bounds->im_min += -ddim * (1. - y_ratio);
	bounds->d_i = bounds->im_max - bounds->im_min;
	bounds->d_r = bounds->re_max - bounds->re_min;
}

void	translate(t_mlx *mlx, int direction)
{
	if (direction == UP)
	{
		mlx->bounds->im_min += mlx->bounds->d_i / SIZE_Y * 50;
		mlx->bounds->im_max += mlx->bounds->d_i / SIZE_Y * 50;
	}
	else if (direction == DOWN)
	{
		mlx->bounds->im_min -= mlx->bounds->d_i / SIZE_Y * 50;
		mlx->bounds->im_max -= mlx->bounds->d_i / SIZE_Y * 50;

	}
	else if (direction == LEFT)
	{
		mlx->bounds->re_min -= mlx->bounds->d_r / SIZE_Y * 50;
		mlx->bounds->re_max -= mlx->bounds->d_r / SIZE_Y * 50;

	}
	else
	{
		mlx->bounds->re_min += mlx->bounds->d_r / SIZE_Y * 50;
		mlx->bounds->re_max += mlx->bounds->d_r / SIZE_Y * 50;
	}
	mlx->bounds->d_r = mlx->bounds->re_max - mlx->bounds->re_min;
	mlx->bounds->d_i = mlx->bounds->im_max - mlx->bounds->im_min;
}
