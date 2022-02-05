/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:44:08 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/05 18:35:03 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "fractol.h"
#include "libft.h"
#include <signal.h>

#define	SIZE_X 2500
#define	SIZE_Y 1250

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
	new->addr = mlx_get_data_addr(new->im_ptr, &new->bpp
				, &new->line_size, &new->endian);
	printf("bits per pixel :%d\n", new->bpp);
	printf("line size      :%d\n", new->line_size);
	printf("endian         :%d\n", new->endian);
	return (new);
}

int	get_color(int t, int r, int g, int b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b); 
}

void	interupt_handler(int signum)
{
	if (signum == SIGINT)
		free_alloc(NULL, 0);
	exit(EXIT_SUCCESS);
}

// static inline void	write_image_line(t_pixel *pixels, char *img)
// {
// 	int		color;

// 	while (pixels)
// 	{
// 		color = pixels->color;
// 		img[0] = color;
// 		img[1] = (color >> 8);
// 		img[2] = (color >> 16);
// 		img[3] = (color >> 24);
// 		img += 4;
// 		pixels = pixels->next;
// 	}
// }


// void	write_image(t_pixel *pixels, char *img);

int	main(int ac, char **av)
{
	if (ac == 1) return (-1);
	t_mlx	*mlx;
	char	*img;
	int		i;
	char	c1;
	char	c2;

	mlx = new_mlx(1000, 1000, "mlx");
	if (!mlx)
		return (printf("nope\n"));
	signal(SIGINT, &interupt_handler);
	img = mlx->addr;
	for (int j = 0; j < 1000 ; j++)
	{
		c1 = (j % 10 < 5) ? 0xFF : 0;
		c2 = (j % 10 < 5) ? 0 : 0xFF;
		i = 0;
		while (i < mlx->line_size)
		{
			img[i] = c1; // blue
			img[i + 1] = 0; // green
			img[i + 2] = c2; // red
			img[i + 3] = atoi(av[1]); // transparence 0 for full
			i += mlx->bpp / 8;
		}
		img += mlx->line_size;
	}
	
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}