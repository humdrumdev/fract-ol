/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:43:34 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/16 20:42:10 by hel-moud         ###   ########.fr       */
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

void	interupt_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("received SIGSIGINT\n");
		free_alloc(NULL, 0);
	}
	exit(EXIT_SUCCESS);
}

int	update_image(t_mlx *mlx)
{
	ft_memcpy(mlx->bounds, mlx->def_bounds, sizeof(t_bounds));
	if (mlx->set == JULIA)
	{
		mlx->j = mlx->def_j;
		mlx->k = mlx->def_k;
	}
	mlx->event = 0;
	put_next_frame(mlx);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	printf("key pressed == %d   mlx == %p\n", keycode, mlx);
	if (keycode == 53 || keycode == 65307)
		update_image(mlx);
	if (keycode >= 123 && keycode <= 126)
		shift(mlx, keycode);
	return (0);
}

int handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	// static int	sigs;

	// if (sigs < 2)
	// {
	// 	sigs++;
	// 	return (0);
	// }
	// sigs = 0;
	printf("button == %d  x == %d  y == %d  %d\n", button, x, y, NULL == mlx);
	if (button == 4 || button == 5)
		return (zoom(mlx, button == 4, x, y), 0);
	if (mlx->set == JULIA)
		change_julia(x, y, mlx);
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

void	init_listners(t_mlx *mlx)
{
	signal(SIGINT, interupt_handler);
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, handle_mouse, mlx);
	// mlx_hook(mlx->win_ptr, ON_MOUSEMOVE, 0, change_julia, mlx);
}
