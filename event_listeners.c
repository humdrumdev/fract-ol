/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:43:34 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 20:28:25 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	on_plus_or_minus(t_mlx *mlx, int key)
{
	if (key == PLUS)
	{
		if (mlx->n_max > 1000)
			mlx->n_max = 30;
		else
			mlx->n_max += 10;
	}
	if (key == MINUS)
	{
		if (mlx->n_max > 40)
			mlx->n_max -= 10;
		else
			mlx->n_max = 30;
	}
	return (update_image(mlx, false));
}

static inline int	on_multiply_or_divide(t_mlx *mlx, int key)
{
	if (key == MULTIPLY)
	{
		if (mlx->radius_sq > 1000000)
			mlx->radius_sq = 4;
		else
			mlx->radius_sq = (mlx->n_max << 1);
	}
	if (key == DIVIDE)
	{
		if (mlx->radius_sq < 4)
			mlx->radius_sq = 4;
		else
			mlx->radius_sq = (mlx->radius_sq >> 1);
	}
	return (update_image(mlx, false));
}

static inline int	on_enter(t_mlx *mlx)
{
	if (!mlx->args->w_dist)
	{
		if (mlx->coloriser == get_color)
			mlx->coloriser = get_periodic_color;
		else
			mlx->coloriser = get_color;
	}
	if (mlx->color_gen < 0.08)
		mlx->color_gen = INV_LOG2 * 100;
	else
		mlx->color_gen = mlx->color_gen * 0.95;
	return (update_image(mlx, false));
}

int	key_hook(int key, t_mlx *mlx)
{
	static int	sigterm;

	if (key == CTRL)
		return (sigterm = 1, 0);
	if ((key == ESC) || (key == KEY_C && sigterm))
		close_win((sigterm = 0, mlx));
	if (key == LEFT || key == RIGHT || key == DOWN || key == UP)
		return (shift(mlx, key), sigterm = 0, 0);
	if (key == PLUS || key == MINUS)
		return (sigterm = 0, on_plus_or_minus(mlx, key));
	if (key == MULTIPLY || key == DIVIDE)
		return (sigterm = 0, on_multiply_or_divide(mlx, key));
	if (key == ENTER && mlx->args->w_shades)
	{
		if (mlx->color_gen < 0.08)
			mlx->color_gen = INV_LOG2 * 100;
		else
			mlx->color_gen *= 0.95;
		return (sigterm = 0, update_image(mlx, false));
	}
	if (key == ENTER)
		return (sigterm = 0, on_enter(mlx));
	return (sigterm = 0, 0);
}

int	handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	static int	sigs;

	if ((button == SCROLL_UP || button == SCROLL_DOWN) && sigs < 4)
		return (sigs++, 0);
	sigs = 0;
	if (button == MOUSE_MIDDLE)
		return (update_image(mlx, true));
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		return (zoom(mlx, button == SCROLL_UP, x, y), 0);
	if (mlx->args->set == JULIA && button == MOUSE_LEFT)
		change_julia(x, y, mlx);
	return (0);
}
