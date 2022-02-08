/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:44:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/08 17:21:52 by hel-moud         ###   ########.fr       */
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


int	handle_mouse(int button, int x, int y, void *param)
{
	printf("button == %d  x == %d  y == %d  %d\n", button, x, y, param == NULL);
	return (0);
}

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

int	update_image(t_mlx *mlx)
{
	double		arr[4] = {-0.25, 0.25, -1., cos(rand())};
	set_bounds(mlx->bounds, (double *)arr);
	char *img = mandelbrot(mlx, mlx->bounds->re_min, mlx->bounds->re_max, mlx->bounds->im_max);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	ft_memcpy(mlx->tmp_addr, img, SIZE_Y * SIZE_X * 4 + 1);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->im_ptr = mlx->tmp_im_ptr;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx->tmp_addr = init_image(mlx, &mlx->tmp_im_ptr, SIZE_X, SIZE_Y);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	printf("key pressed == %d\n", keycode);
	if (keycode == 53)
		update_image(mlx);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 1) return (av[0][0]);
	t_mlx		*mlx;
	char		*img;
	t_bounds	bounds;
	double		arr[4] = {-2., 2., -1.5, 1.5};

	mlx = new_mlx(SIZE_X, SIZE_Y, "mlx");
	if (!mlx)
		return (printf("nope\n"));
	mlx->im_width = SIZE_X;
	mlx->im_height = SIZE_Y;
	signal(SIGINT, interupt_handler);
	set_bounds(&bounds, (double *)arr);
	mlx->bounds = &bounds;
	img = mandelbrot(mlx, bounds.re_min, bounds.re_max, bounds.im_max);

	ft_memcpy(mlx->addr, img, SIZE_X * SIZE_Y * 4 + 1);

	
	 t_vars vars = {.mlx = mlx->mlx_ptr, .win = mlx->win_ptr};
	mlx_key_hook(vars.win, key_hook, mlx);
	mlx_mouse_hook(vars.win, key_hook, mlx);
	
	//int (*f)(int button, int x, int y, void *param)
	//void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	mlx_hook(vars.win, ON_MOUSEUP, 0, handle_mouse, NULL);
	// mlx_hook(vars.win, ON_MOUSEMOVE, 0, handle_mouse, NULL);
	
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}