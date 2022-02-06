/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:44:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/06 16:49:33 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	new->im_ptr = mlx_new_image(new->mlx_ptr, im_width, im_height);
	if (!new->im_ptr)
	{
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free(new), NULL);
	}
	new->bpp = 0;
	new->line_size = 0;
	new->endian = 0;
	new->tmp_img = NULL;
	new->addr = mlx_get_data_addr(new->im_ptr, &new->bpp
				, &new->line_size, &new->endian);
	printf("bits per pixel :%d\n", new->bpp);
	printf("line size      :%d\n", new->line_size);
	printf("endian         :%d\n", new->endian);
	return (new);
}

// int	get_color(int t, int r, int g, int b)
// {
// 	return ((t << 24) | (r << 16) | (g << 8) | b); 
// }

void	interupt_handler(int signum)
{
	if (signum == SIGINT)
		free_alloc(NULL, 0);
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

int	main(int ac, char **av)
{
	if (ac < 1) return (av[0][0]);
	t_mlx	*mlx;
	char	*img;
	int		i;
	// double	t;

	mlx = new_mlx(1000, 1000, "mlx");
	if (!mlx)
		return (printf("nope\n"));
	signal(SIGINT, &interupt_handler);
	img = init_pixel_img(1000, 1000);
	for (int j = 0; j < 1000 ; j++)
	{
		i = 0;
		while (i < 1000)
		{
			// mlx_put_pixel_img(mlx, i, j, (j % 10 < 5) ? 0x00FF0000 : 0x000000FF);
			*(int *)(img + j * mlx->line_size + (mlx->bpp / 8) * i) = (j % 10 < 5) ? get_color(cos((double)rand())) : 0x00000000;
			i++;
		}
	}
	
	ft_memcpy(mlx->addr, img, 1000 * 1000 * 4 + 1);

	
	t_vars vars = {.mlx = mlx->mlx_ptr, .win = mlx->win_ptr};
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, key_hook, &vars);
	
	//int (*f)(int button, int x, int y, void *param)
	//void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	mlx_hook(vars.win, ON_MOUSEUP, 0, handle_mouse, NULL);
	// mlx_hook(vars.win, ON_MOUSEMOVE, 0, handle_mouse, NULL);
	
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx_string_put(vars.mlx, vars.win, -5, -15, 0x00ff00ff, ".");
	mlx_loop(mlx->mlx_ptr);
	return (0);
}