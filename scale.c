/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:03:42 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/16 20:42:58 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	scale(t_mlx *mlx, int direction, double x, double y)
{
	double	x_ratio;
	double	y_ratio;
	double	scale_factor;
	double	ddre;
	double	ddim;

	x_ratio = x / mlx->im_width;
	y_ratio = y / mlx->im_height;
	scale_factor = 0.8 + (direction != 1) * 1.2;
	ddre = (scale_factor * mlx->bounds->d_r) - mlx->bounds->d_r;
	ddim = (scale_factor * mlx->bounds->d_i) - mlx->bounds->d_i;
	mlx->bounds->re_max += ddre * (1. - x_ratio);
	mlx->bounds->re_min += -ddre * x_ratio;
	mlx->bounds->im_max += ddim * y_ratio;
	mlx->bounds->im_min += -ddim * (1. - y_ratio);
	mlx->bounds->d_i = mlx->bounds->im_max - mlx->bounds->im_min;
	mlx->bounds->d_r = mlx->bounds->re_max - mlx->bounds->re_min;
}

static inline void	translate(t_mlx *mlx, int direction)
{
	double	dist;

	dist = mlx->draw->px_size * mlx->px_move;
	if (direction == UP)
	{
		mlx->bounds->im_min += dist;
		mlx->bounds->im_max += dist;
	}
	if (direction == DOWN)
	{
		mlx->bounds->im_min -= dist;
		mlx->bounds->im_max -= dist;
	}
	if (direction == RIGHT)
	{
		mlx->bounds->re_min -= dist;
		mlx->bounds->re_max -= dist;
	}
	if (direction == LEFT)
	{
		mlx->bounds->re_min += dist;
		mlx->bounds->re_max += dist;
	}
	mlx->bounds->d_r = mlx->bounds->re_max - mlx->bounds->re_min;
	mlx->bounds->d_i = mlx->bounds->im_max - mlx->bounds->im_min;
}

void	shift(t_mlx *mlx, int direction)
{
	mlx->event = direction;
	translate(mlx, direction);
	put_next_frame(mlx);
}

void	zoom(t_mlx *mlx, int direction, int x, int y)
{
	mlx->event = 0;
	scale(mlx, direction, x, y);
	put_next_frame(mlx);
}
