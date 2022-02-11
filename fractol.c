/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:44:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/11 16:08:56 by hel-moud         ###   ########.fr       */
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

t_mlx	*new_mlx(int im_width, int im_height, char *title)
{
	t_mlx	*new;

	new = NULL;
	if (free_alloc((void **)&new, sizeof(t_mlx)))
		return (NULL);
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
		return (free(new), NULL);
	new->win_ptr = mlx_new_window(new->mlx_ptr, SIZE_X, SIZE_Y, title);
	if (!new->win_ptr)
		return (free(new->mlx_ptr), free(new), NULL);
	new->addr = init_image(new, &new->im_ptr, im_width, im_height);
	if (!new->addr)
	{
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free(new), NULL);
	}
	new->tmp_addr = init_image(new, &new->tmp_im_ptr, im_width, im_height);
	if (!new->tmp_addr)
	{
		mlx_destroy_image(new->mlx_ptr, new->im_ptr);
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free(new), NULL);
	}
	return (new);
}

// int	get_color(int t, int r, int g, int b)
// {
// 	return ((t << 24) | (r << 16) | (g << 8) | b);
// }

void	interupt_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("received SIGSIGINT\n");
		free_alloc(NULL, 0);
	}
	exit(EXIT_SUCCESS);
}

/*
static inline void	mlx_put_pixel_img(t_mlx *mlx, int x, int y, int color)
{
	char	*img;

	img = mlx->addr + (y * mlx->line_size + (mlx->bpp / 8) * x);
	*(int *)img = color;
}
static inline void	mlx_put_pixel_buf(t_mlx *mlx, int x, int y, int c)
{
	*(int *)(mlx->tmp_img + (y * mlx->line_size + (mlx->bpp / 8) * x)) = c;
}

*/


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

void	scale(t_bounds *bounds, int direction, double x, double y)
{
	double	x_ratio;
	double	y_ratio;
	double	scale_factor;
	double	ddre;
	double	ddim;

	x_ratio = x / SIZE_X;
	y_ratio = y / SIZE_Y;
	if (direction == 1)
		scale_factor = 0.8;
	else
		scale_factor = 2.;
	ddre = (scale_factor * bounds->d_r) - bounds->d_r;
	ddim = (scale_factor * bounds->d_i) - bounds->d_i;
	bounds->re_max += ddre * (1. - x_ratio);
	bounds->re_min += -ddre * x_ratio;
	bounds->im_max += ddim * y_ratio;
	bounds->im_min += -ddim * (1. - y_ratio);
	bounds->d_i = bounds->im_max - bounds->im_min;
	bounds->d_r = bounds->re_max - bounds->re_min;
}

int	update_image(t_mlx *mlx)
{
	double		arr[4] = {-2., 2., -2., 2.};
	set_bounds(mlx->bounds, (double *)arr);
	char *img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, SIZE_Y * SIZE_X * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, SIZE_X, SIZE_Y);
	return (0);
}

void	translate(t_mlx *mlx, int direction)
{
	if (direction == UP)
	{
		mlx->bounds->im_min += mlx->bounds->d_i / SIZE_Y * 50;
		mlx->bounds->im_max += mlx->bounds->d_i / SIZE_Y * 50;
	}
	else if (direction == DOWN)
	{
		mlx->bounds->im_min -= mlx->bounds->d_i / SIZE_Y * 50;
		mlx->bounds->im_max -= mlx->bounds->d_i / SIZE_Y * 50;
	}
	else if (direction == LEFT)
	{
		mlx->bounds->re_min -= mlx->bounds->d_r / SIZE_Y * 50;
		mlx->bounds->re_max -= mlx->bounds->d_r / SIZE_Y * 50;
	}
	else
	{
		mlx->bounds->re_min += mlx->bounds->d_r / SIZE_Y * 50;
		mlx->bounds->re_max += mlx->bounds->d_r / SIZE_Y * 50;
	}
	mlx->bounds->d_r = mlx->bounds->re_max - mlx->bounds->re_min;
	mlx->bounds->d_i = mlx->bounds->im_max - mlx->bounds->im_min;
}

void	shift(t_mlx *mlx, int direction)
{
	translate(mlx, direction);
	char *img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, SIZE_Y * SIZE_X * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, SIZE_X, SIZE_Y);
}

void	zoom(t_mlx *mlx, int direction, int x, int y)
{
	printf("here\n");
	scale(mlx->bounds, direction, x, y);
	char *img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, SIZE_Y * SIZE_X * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, SIZE_X, SIZE_Y);
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
	printf("button == %d  x == %d  y == %d  %d\n", button, x, y, NULL == mlx);
	if (button == 4 || button == 5)
		zoom(mlx, button == 4, x, y);
	return (0);
}

int	change_julia(int x, int y, t_mlx *mlx)
{
	if (x < SIZE_X && y < SIZE_Y && (mlx->j != x || mlx->k != y))
	{
		mlx->j = x;
		mlx->k = y;
		char *img = mlx->draw->draw(mlx, get_periodic_color, INV_LOG2);
		mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
		ft_memcpy(mlx->tmp_addr, img, SIZE_Y * SIZE_X * 4 + 1);
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->im_ptr = mlx->tmp_im_ptr;
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
		mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, SIZE_X, SIZE_Y);
	}
	return (0);
}

/*
int	main(int ac, char **av)
{
	if (ac < 1) return (av[0][0]);
	t_mlx		*mlx;
	char		*img;
	t_bounds	bounds;
	double		arr[4] = {-2., 2., -2., 2.};

	mlx = new_mlx(SIZE_X, SIZE_Y, "mlx");
	if (!mlx)
		return (printf("nope\n"));
	signal(SIGINT, interupt_handler);
	img = julia(mlx, get_periodic_color, INV_LOG2);

	ft_memcpy(mlx->addr, img, SIZE_X * SIZE_Y * 4 + 1);


	t_vars vars = {.mlx = mlx->mlx_ptr, .win = mlx->win_ptr};
	mlx_key_hook(vars.win, key_hook, mlx);
	mlx_mouse_hook(vars.win, handle_mouse, mlx);

	//int (*f)(int button, int x, int y, void *param)
	//void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)

	// mlx_hook(vars.win, ON_MOUSEUP, 0, handle_mouse, mlx);
	// mlx_hook(vars.win, ON_MOUSEDOWN, 0, handle_mouse, mlx);
	// mlx_hook(vars.win, 9, 0, handle_mouse, mlx);
	// mlx_hook(vars.win, 10, 0, handle_mouse, mlx);

	mlx_hook(vars.win, ON_MOUSEMOVE, 0, change_julia, mlx);

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
*/