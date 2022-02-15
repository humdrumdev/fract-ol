/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:43:34 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/15 14:49:54 by hel-moud         ###   ########.fr       */
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
	char	*img;

	ft_memcpy(mlx->bounds, mlx->def_bounds, sizeof(t_bounds));
	if (mlx->set == JULIA)
	{
		mlx->j = mlx->def_j;
		mlx->k = mlx->def_k;
	}
	mlx->event = 0;
	img = mlx->draw->draw(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, mlx->im_height * mlx->im_width * 4 + 1);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx->addr = mlx->tmp_addr;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
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
	static int	sigs;

	if (sigs < 2)
	{
		sigs++;
		return (0);
	}
	sigs = 0;
	printf("button == %d  x == %d  y == %d  %d\n", button, x, y, NULL == mlx);
	if (button == 4 || button == 5)
		return (zoom(mlx, button == 4, x, y), 0);
	if (mlx->set == JULIA)
		change_julia(x, y, mlx);
	return (0);
}

int	change_julia(int x, int y, t_mlx *mlx)
{
	char	*img;

	if (x < mlx->im_width && y < mlx->im_height && (mlx->j != x || mlx->k != y))
	{
		mlx->event = 0;
		mlx->j = x * mlx->draw->px_size + mlx->bounds->re_min;
		mlx->k = y * mlx->draw->px_size + mlx->bounds->im_min;
		ft_memcpy(mlx->bounds, mlx->def_bounds, sizeof(t_bounds));
		img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
		ft_memcpy(mlx->tmp_addr, img, mlx->im_height * mlx->im_width * 4 + 1);
		mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
		mlx->im_ptr = mlx->tmp_im_ptr;
		mlx->addr = mlx->tmp_addr;
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
		mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
	}
	return (0);
}

void	init_listners(t_mlx *mlx)
{
	signal(SIGINT, interupt_handler);
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, handle_mouse, mlx);
}
