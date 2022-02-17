/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:43:34 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/17 23:18:00 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*init_image(t_mlx *mlx, void **img, int im_width, int im_height)
{
	char	*addr;

	*img = mlx_new_image(mlx->mlx_ptr, im_width, im_height);
	if (!*img)
		return (NULL);
	addr = mlx_get_data_addr(*img, &mlx->bpp, &mlx->line_size, &mlx->endian);
	return (addr);
}


int	update_image(t_mlx *mlx, bool new)
{
	if (new)
		ft_memcpy(mlx->bounds, mlx->def_bounds, sizeof(t_bounds));
	if (mlx->args->set == JULIA)
	{
		mlx->j = mlx->def_j;
		mlx->k = mlx->def_k;
	}
	mlx->event = 0;
	put_next_frame(mlx);
	return (0);
}


int	change_julia(int x, int y, t_mlx *mlx)
{
	if (x < mlx->im_width && y < mlx->im_height && (mlx->j != x || mlx->k != y))
	{
		mlx->event = 0;
		mlx->j = x * mlx->draw->px_size + mlx->bounds->re_min;
		mlx->k = y * mlx->draw->px_size + mlx->bounds->im_min;
		ft_memcpy(mlx->bounds, mlx->def_bounds, sizeof(t_bounds));
		put_next_frame(mlx);
	}
	return (0);
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->tmp_im_ptr);
	clean_exit(EXIT_SUCCESS, "process terminated\n", NULL, NULL);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	static int	sigterm;

	if (keycode == CTRL)
		return (sigterm = 1, 0);
	if ((keycode == ESC) || (keycode == KEY_C && sigterm))
		(sigterm = 0, close_win(mlx));
	if (keycode == LEFT || keycode == RIGHT || keycode == DOWN ||  keycode == UP)
		return (shift(mlx, keycode), sigterm = 0, 0);
	if (keycode == PLUS || keycode == MINUS)
	{
		if (keycode == PLUS)
		{
			mlx->n_max = TERNARY((mlx->n_max > 1000), 30, (mlx->n_max + 10));
			printf("n max became == %d\n", mlx->n_max);
		}
		if (keycode == MINUS)
			mlx->n_max = TERNARY((mlx->n_max > 40), (mlx->n_max - 10), 30);
		return (sigterm = 0, update_image(mlx, false));
	}
	if (keycode == MULTIPLY || keycode == DIVIDE)
	{
		if (keycode == MULTIPLY)
			mlx->radius_sq = TERNARY((mlx->radius_sq > 1000000), 4, (mlx->n_max << 1));
		if (keycode == DIVIDE)
			mlx->radius_sq = TERNARY((mlx->radius_sq < 4), 4, (mlx->radius_sq >> 1));
		return (sigterm = 0, update_image(mlx, false));
	}
	if (keycode == ENTER && mlx->args->w_shades)
	{
		mlx->color_gen = TERNARY((mlx->color_gen < 0.08), (INV_LOG2 * 100), (mlx->color_gen * 0.95));
		return (sigterm = 0, update_image(mlx, false));
	}
	if (keycode == ENTER)
	{
		if (!mlx->args->w_dist)
			mlx->coloriser = TERNARY((mlx->coloriser == get_color), get_periodic_color, get_color);
		mlx->color_gen = TERNARY((mlx->color_gen < 0.08), (INV_LOG2 * 100), (mlx->color_gen * 0.95));
		return (sigterm = 0, update_image(mlx, false));
	}
	return (sigterm = 0, 0);
}

int handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	static int	sigs;

	if ((button == SCROLL_UP || button == SCROLL_DOWN) && sigs < 4)
		return (sigs++ , 0);
	sigs = 0;
	if (button == MOUSE_MIDDLE)
		return (update_image(mlx, true));
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		return (zoom(mlx, button == SCROLL_UP, x, y), 0);
	if (mlx->args->set == JULIA && button == MOUSE_LEFT)
		change_julia(x, y, mlx);
	return (0);
}


void	init_listners(t_mlx *mlx)
{
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, handle_mouse, mlx);
	mlx_hook(mlx->win_ptr, ON_DESTROY, 0, close_win, mlx);
}
