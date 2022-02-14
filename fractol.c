/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:44:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/14 18:11:35 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <string.h>
#include <time.h>

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


char	*init_pixel_img(int width, int height)
{
	char	*pixels;

	pixels = NULL;
	if (free_alloc((void **)&pixels, (height * width * 4 + 1) * sizeof(char)))
		return (NULL);
	pixels[height * width * 4] = '\0';
	return (pixels);
}

/*
void	cpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
		(dest[i] = src[i], i++);
}
*/

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


char	*rev(char *src, char *a, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		a[i] = src[size -1 - i - 1];
	}
	a[1000 * 1000 * 4] = 0;
	return (a);
}

void	set_bounds(t_bounds *bounds, double *arr)
{
	bounds->re_min = arr[0];
	bounds->re_max = arr[1];
	bounds->im_min = arr[2];
	bounds->im_max = arr[3];
	bounds->d_r = bounds->re_max - bounds->re_min;
	bounds->d_i = bounds->im_max - bounds->im_min;
}

// int	has_changed(t_mlx *mlx, int x, int y)
// {
// 	double	real_part;
// 	double	im_part;

// 	real_part = mlx->bounds->re_min + x * mlx->draw->px_size;
// 	im_part = mlx->bounds->im_max - y * mlx->draw->px_size;

// 	if (real_part >= mlx->prev_bounds->re_min)
// 		if (real_part <= mlx->prev_bounds->re_max)
// 			if (im_part <= mlx->prev_bounds->im_max)
// 				if (im_part >= mlx->prev_bounds->im_min)
// 					return (0);
// 	return (1);
// }

void	scale(t_mlx *mlx, int direction, double x, double y)
{
	double	x_ratio;
	double	y_ratio;
	double	scale_factor;
	double	ddre;
	double	ddim;

	x_ratio = x / mlx->im_width;
	y_ratio = y / mlx->im_height;
	if (direction == 1)
		scale_factor = 0.8;
	else
		scale_factor = 2.;
	ddre = (scale_factor * mlx->bounds->d_r) - mlx->bounds->d_r;
	ddim = (scale_factor * mlx->bounds->d_i) - mlx->bounds->d_i;
	mlx->bounds->re_max += ddre * (1. - x_ratio);
	mlx->bounds->re_min += -ddre * x_ratio;
	mlx->bounds->im_max += ddim * y_ratio;
	mlx->bounds->im_min += -ddim * (1. - y_ratio);
	mlx->bounds->d_i = mlx->bounds->im_max - mlx->bounds->im_min;
	mlx->bounds->d_r = mlx->bounds->re_max - mlx->bounds->re_min;
}

int	update_image(t_mlx *mlx)
{
	double		arr[4] = {-2., 2., -2., 2.};
	set_bounds(mlx->bounds, (double *)arr);
	mlx->event = 0;
	char *img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, mlx->im_height * mlx->im_width * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->addr = mlx->tmp_addr;
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
	return (0);
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
	mlx->event = direction;
	translate(mlx, direction);
	char *img = mlx->draw->draw(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, mlx->im_width * mlx->im_height * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->addr = mlx->tmp_addr;
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
}

void	zoom(t_mlx *mlx, int direction, int x, int y)
{
	mlx->event = 0;
	scale(mlx, direction, x, y);
	char *img = mlx->draw->draw(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, mlx->im_width * mlx->im_height * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->addr = mlx->tmp_addr;
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
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

	if (sigs < 3)
	{
		sigs++;
		return (0);
	}

	printf("button == %d  x == %d  y == %d  %d\n", button, x, y, NULL == mlx);
	if (mlx->set != JULIA)
	{
		if (button == 4 || button == 5)
		{
			if (sigs < 3)
				sigs++;
			else
			{
				zoom(mlx, button == 4, x, y);
				sigs = 0;
			}
		}
	}
	else
	{
		if (button == 4 || button == 5)
		{
			if (sigs < 3)
				sigs++;
			else
			{
				zoom(mlx, button == 4, x, y);
				sigs = 0;
			}
		}
		else
			change_julia(x, y, mlx);
	}
	return (0);
}

int	change_julia(int x, int y, t_mlx *mlx)
{
	if (x < mlx->im_width && y < mlx->im_height && (mlx->j != x || mlx->k != y))
	{
		mlx->event = 0;
		mlx->j = x * mlx->draw->px_size + mlx->bounds->re_min;
		mlx->k = y * mlx->draw->px_size + mlx->bounds->im_min;
		char *img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
		mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
		ft_memcpy(mlx->tmp_addr, img, mlx->im_height * mlx->im_width * 4 + 1);
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->im_ptr = mlx->tmp_im_ptr;
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
		mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, mlx->im_width, mlx->im_height);
	}
	return (0);
}
