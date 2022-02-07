/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:44:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/07 18:28:05 by hel-moud         ###   ########.fr       */
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

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("key pressed == %d\n", keycode);
	return (0);
}

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

int	main(int ac, char **av)
{
	if (ac < 1) return (av[0][0]);
	t_mlx	*mlx;
	char	*img;
	// int		i;
	// double	t;

	mlx = new_mlx(SIZE_X, SIZE_Y, "mlx");
	if (!mlx)
		return (printf("nope\n"));
	mlx->im_width = SIZE_X;
	mlx->im_height = SIZE_Y;
	signal(SIGINT, &interupt_handler);
	// img = init_pixel_img(1000, 1000);
	// srand(time(0));
	// for (int j = 0; j < 1000 ; j++)
	// {
	// 	i = 0;
	// 	while (i < 1000)
	// 	{
	// 		// mlx_put_pixel_img(mlx, i, j, (j % 10 < 5) ? 0x00FF0000 : 0x000000FF);
	// 		*(int *)(img + j * mlx->line_size + (mlx->bpp / 8) * i) = (i < j) && ((j % 100 < 50) || (j % 100 >= 80 )) ? get_color(cos((double)rand())) : 0x00000000;
	// 		i++;
	// 	}
	// }
	
	img = mandelbrot(mlx, -1.5, -1.25, 0.25);

	ft_memcpy(mlx->addr, img, SIZE_X * SIZE_Y * 4 + 1);

	
	t_vars vars = {.mlx = mlx->mlx_ptr, .win = mlx->win_ptr};
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, key_hook, &vars);
	
	//int (*f)(int button, int x, int y, void *param)
	//void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	mlx_hook(vars.win, ON_MOUSEUP, 0, handle_mouse, NULL);
	// mlx_hook(vars.win, ON_MOUSEMOVE, 0, handle_mouse, NULL);
	
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	// mlx->tmp_addr = rev(mlx->addr, mlx->tmp_addr,1000 * 1000 * 4 + 1);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->tmp_im_ptr, 1000, 0);
	// mlx_string_put(vars.mlx, vars.win, 1000 -5, 500 -15, 0x00ff00ff, "center");
	mlx_loop(mlx->mlx_ptr);
	return (0);
}