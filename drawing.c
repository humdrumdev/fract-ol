/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:03:14 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/12 19:35:47 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	has_changed(t_mlx *mlx, int x, int y)
{
	if (mlx->event == DOWN)
		return (y >= (SIZE_Y - 50));
	if (mlx->event == UP)
		return (y < 50);
	if (mlx->event == LEFT)
		return (x >= (SIZE_X - 50));
	if (mlx->event == RIGHT)
		return (x < 50);
	return (0);
}

static void	copy_pixels(t_mlx *mlx, t_draw *vars)
{
	int	x;
	int	y;
	int	index;

	if (mlx->event == DOWN)
	{
		y = 0;
		while (y < SIZE_Y - 50)
		{
			x = 0;
			while (x < SIZE_X)
			{
				index = y * mlx->line_size + 4 * x;
				*(int *)(vars->img + index) = *(int *)(mlx->addr + index + 50 * mlx->line_size);
				x++;
			}
			y++;
		}
	}
	if (mlx->event == UP)
	{
		y = 50;
		while (y < SIZE_Y)
		{
			x = 0;
			while (x < SIZE_X)
			{
				index = y * mlx->line_size + 4 * x;
				*(int *)(vars->img + index) = *(int *)(mlx->addr + index - 50 * mlx->line_size);
				x++;
			}
			y++;
		}
		
	}
	if (mlx->event == RIGHT)
	{
		y = 0;
		while (y < SIZE_Y)
		{
			x = 50;
			while (x < SIZE_X)
			{
				index = y * mlx->line_size + 4 * x;
				*(int *)(vars->img + index) = *(int *)(mlx->addr + index - 50 * 4);
				x++;
			}
			y++;
		}
	}
	if (mlx->event == LEFT)
	{
		y = 0;
		while (y < SIZE_Y)
		{
			x = 0;
			while (x < SIZE_X - 50)
			{
				index = y * mlx->line_size + 4 * x;
				*(int *)(vars->img + index) = *(int *)(mlx->addr + index + 50 * 4);
				x++;
			}
			y++;
		}
	}
}

char	*mandelbrot(t_mlx *mlx, t_color coloriser, double color_gen)
{
	t_draw		*vars;
	t_bounds	*bounds;

	vars = mlx->draw;
	bounds = mlx->bounds;
	mlx->set = MANDELBROT;
	if (free_alloc((void **)&vars->img, mlx->im_height * mlx->im_width * 4 + 1))
		return (NULL);
	vars->px_size = bounds->d_r / mlx->im_width;
	vars->line_width = bounds->d_r / mlx->im_height;
	if (mlx->event >= 123 && mlx->event <= 126)
		copy_pixels(mlx, vars);
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
		{
			if (mlx->event >= 123 && mlx->event <= 126)
			{
				if (has_changed(mlx, vars->x, vars->y))
					colorise_pixel(mlx, vars, coloriser, color_gen);
			}
			else
				colorise_pixel(mlx, vars, coloriser, color_gen);
			vars->x++;
		}
		vars->y++;
	}
	return (vars->img[mlx->im_height * mlx->im_width * 4] = '\0', vars->img);
}

char	*julia(t_mlx *mlx, t_color coloriser, double color_gen)
{
	t_draw		*vars;
	t_bounds	*bounds;

	vars = mlx->draw;
	bounds = mlx->bounds;
	mlx->set = JULIA;
	if (free_alloc((void **)&vars->img, mlx->im_height * mlx->im_width * 4 + 1))
		return (NULL);
	vars->px_size = bounds->d_r / mlx->im_width;
	vars->line_width = bounds->d_r / mlx->im_height;
	if (mlx->event >= 123 && mlx->event <= 126)
		copy_pixels(mlx, vars);
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
		{
			if (mlx->event >= 123 && mlx->event <= 126)
			{
				if (has_changed(mlx, vars->x, vars->y))
					colorise_pixel(mlx, vars, coloriser, color_gen);
			}
			else
				colorise_pixel(mlx, vars, coloriser, color_gen);
			vars->x++;
		}
		vars->y++;
	}
	return (vars->img[mlx->im_height * mlx->im_width * 4] = '\0', vars->img);
}

char	*doublebrot(t_mlx *mlx, t_color coloriser, double color_gen)
{
	t_draw		*vars;
	t_bounds	*bounds;

	vars = mlx->draw;
	bounds = mlx->bounds;
	mlx->set = DOUBLEBROT;
	if (free_alloc((void **)&vars->img, mlx->im_height * mlx->im_width * 4 + 1))
		return (NULL);
	vars->px_size = bounds->d_r / mlx->im_width;
	vars->line_width = bounds->d_r / mlx->im_height;
	if (mlx->event >= 123 && mlx->event <= 126)
		copy_pixels(mlx, vars);
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
		{
			if (mlx->event >= 123 && mlx->event <= 126)
			{
				if (has_changed(mlx, vars->x, vars->y))
					colorise_pixel(mlx, vars, coloriser, color_gen);
			}
			else
				colorise_pixel(mlx, vars, coloriser, color_gen);
			vars->x++;
		}
		vars->y++;
	}
	return (vars->img[mlx->im_height * mlx->im_width * 4] = '\0', vars->img);
}