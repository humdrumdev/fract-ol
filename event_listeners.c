/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:43:34 by hel-moud          #+#    #+#             */
/*   Updated: 2022/03/12 14:06:16 by hel-moud         ###   ########.fr       */
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
	if (mlx->color_gen < 0.08)
		mlx->color_gen = INV_LOG2 * 100;
	else
		mlx->color_gen = mlx->color_gen * 0.95;
	return (update_image(mlx, false));
}

static inline int	on_del(t_mlx *mlx)
{
	if (mlx->color_gen >= 0.08)
		mlx->color_gen /= 0.95;
	else
		mlx->color_gen = INV_LOG2 * 100;
	return (update_image(mlx, false));
}

static inline int	on_space(t_mlx *mlx)
{
	if (mlx->args->set == MANDELBROT)
		mlx->args->set = DOUBLEBROT;
	else if (mlx->args->set == JULIA)
		mlx->args->set = MANDELBROT;
	else
		mlx->args->set = JULIA;
	return (update_image(mlx, true));
}

int	key_hook(int key, t_mlx *mlx)
{
	static int	sigterm;

	if (key == SP)
		return (sigterm = 0, on_space(mlx));
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
	if (key == ENTER)
		return (sigterm = 0, on_enter(mlx));
	if (key == DEL)
		return (sigterm = 0, on_del(mlx));
	return (sigterm = 0, 0);
}

int	handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	static int	sigs;

	if ((button == SCROLL_UP || button == SCROLL_DOWN) && sigs < 4)
		return (sigs++, 0);
	sigs = 0;
	if (button == MOUSE_MIDDLE || (button == MOUSE_RIGHT && !mlx->args->w_shades))
	{
		if (button == MOUSE_RIGHT)
			mlx->args->toggle_coloriser = !mlx->args->toggle_coloriser;
		return (update_image(mlx, button == MOUSE_MIDDLE));
	}
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		return (zoom(mlx, button == SCROLL_UP, x, y), 0);
	if (mlx->args->set == JULIA && button == MOUSE_LEFT)
		change_julia(x, y, mlx);
	return (0);
}
