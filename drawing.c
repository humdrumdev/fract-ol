/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:03:14 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/11 19:01:18 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
			colorise_pixel(mlx, vars, coloriser, color_gen);
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
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
			colorise_pixel(mlx, vars, coloriser, color_gen);
		vars->y++;
	}
	return (vars->img[mlx->im_height * mlx->im_width * 4] = '\0', vars->img);
}

char	*mandelbrot2(t_mlx *mlx, t_color coloriser, double color_gen)
{
	t_draw		*vars;
	t_bounds	*bounds;

	vars = mlx->draw;
	bounds = mlx->bounds;
	mlx->set = MANDELBROT2;
	if (free_alloc((void **)&vars->img, mlx->im_height * mlx->im_width * 4 + 1))
		return (NULL);
	vars->px_size = bounds->d_r / mlx->im_width;
	vars->line_width = bounds->d_r / mlx->im_height;
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
			colorise_pixel(mlx, vars, coloriser, color_gen);
		vars->y++;
	}
	return (vars->img[mlx->im_height * mlx->im_width * 4] = '\0', vars->img);
}