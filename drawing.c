/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:03:14 by hel-moud          #+#    #+#             */
/*   Updated: 2022/03/16 16:43:21 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	has_changed(t_mlx *mlx, int x, int y)
{
	if (mlx->event == DOWN)
		return (y >= (mlx->im_height - mlx->px_move));
	if (mlx->event == UP)
		return (y < mlx->px_move);
	if (mlx->event == LEFT)
		return (x >= (mlx->im_width - mlx->px_move));
	if (mlx->event == RIGHT)
		return (x < mlx->px_move);
	return (0);
}

static inline void	reuse(t_region *reg, t_mlx *mlx, t_draw *vars)
{
	int	x;
	int	y;
	int	index;
	int	color;

	y = reg->y_start;
	while (y < reg->y_end)
	{
		x = reg->x_start;
		while (x < reg->x_end)
		{
			index = y * mlx->line_size + (mlx->bpp / 8) * x;
			color = *(int *)(mlx->addr + index + reg->offset);
			*(int *)(vars->img + index) = color;
			x++;
		}
		y++;
	}
}

static void	copy_pixels(t_mlx *mlx, t_draw *vars)
{
	t_region	region;

	region.offset = 0.;
	if (mlx->event == DOWN)
		region.offset = mlx->px_move * mlx->line_size;
	if (mlx->event == UP)
		region.offset = -mlx->px_move * mlx->line_size;
	if (mlx->event == RIGHT)
		region.offset = -(mlx->bpp / 8) * mlx->px_move;
	if (mlx->event == LEFT)
		region.offset = (mlx->bpp / 8) * mlx->px_move;
	region.y_start = mlx->px_move * (mlx->event == UP);
	region.y_end = mlx->im_height - mlx->px_move * (mlx->event == DOWN);
	region.x_start = mlx->px_move * (mlx->event == RIGHT);
	region.x_end = mlx->im_width - mlx->px_move * (mlx->event == LEFT);
	reuse(&region, mlx, vars);
}

static inline void	colorise(t_mlx *mlx, t_draw *vars)
{
	if (mlx->event == LEFT || mlx->event == UP
		|| mlx->event == DOWN || mlx->event == RIGHT)
	{
		if (has_changed(mlx, vars->x, vars->y))
			colorise_pixel(mlx, vars);
	}
	else
		colorise_pixel(mlx, vars);
}

void	*copy_routine(void *arg)
{
	t_mlx		*mlx;
	t_draw		*vars;

	mlx = (t_mlx *)arg;
	vars = mlx->draw;
	copy_pixels(mlx, vars);
	return (NULL);
}

void	*drawing_routine(void *arg)
{
	t_draw		*vars;
	t_mlx		*mlx;

	mlx = (t_mlx *)arg;
	vars = mlx->draw;
	vars->y = 0;
	while (vars->y < mlx->im_height)
	{
		vars->x = 0;
		while (vars->x < mlx->im_width)
		{
			colorise(mlx, vars);
			vars->x++;
		}
		vars->y++;
	}
	return (NULL);
}

void	draw(t_mlx *mlx)
{
	t_draw		*vars;
	t_bounds	*bounds;
	pthread_t	th;
	pthread_t	th2;

	vars = mlx->draw;
	bounds = mlx->bounds;
	vars->img = mlx->tmp_addr;
	vars->px_size = bounds->d_r / mlx->im_width;
	vars->line_width = bounds->d_r / mlx->im_height;
	if (mlx->event == LEFT || mlx->event == UP
		|| mlx->event == DOWN || mlx->event == RIGHT)
		pthread_create(&th, NULL, copy_routine, mlx);
	pthread_create(&th2, NULL, drawing_routine, mlx);
	if (mlx->event == LEFT || mlx->event == UP
		|| mlx->event == DOWN || mlx->event == RIGHT)
		pthread_join(th, NULL);
	pthread_join(th2, NULL);
	vars->img[mlx->im_height * mlx->im_width * 4] = '\0';
}
