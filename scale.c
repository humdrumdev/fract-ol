/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:03:42 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/15 14:53:31 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scale(t_mlx *mlx, int direction, double x, double y)
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

void	translate(t_mlx *mlx, int direction)
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
	char	*img;

	mlx->event = direction;
	translate(mlx, direction);
	img = mlx->draw->draw(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, mlx->im_width * mlx->im_height * 4 + 1);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx->addr = mlx->tmp_addr;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
}

void	zoom(t_mlx *mlx, int direction, int x, int y)
{
	char	*img;

	mlx->event = 0;
	scale(mlx, direction, x, y);
	img = mlx->draw->draw(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, mlx->im_width * mlx->im_height * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx->addr = mlx->tmp_addr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
}
