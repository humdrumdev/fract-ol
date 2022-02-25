/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:27:04 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/25 21:02:30 by hel-moud         ###   ########.fr       */
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
	if (mlx->args->set == JULIA && new)
	{
		mlx->j = mlx->def_j;
		mlx->k = mlx->def_k;
	}
	mlx->event = 0;
	put_next_frame(mlx);
	if (new)
		show_use(mlx);
	return (0);
}

int	change_julia(int x, int y, t_mlx *mlx)
{
	if (x < mlx->im_width && y < mlx->im_height
		&& (mlx->j != x || mlx->k != y))
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
	mlx_destroy_image(mlx->mlx_ptr, mlx->tmp_im_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->im_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx->mlx_ptr);
	clean_exit(EXIT_SUCCESS, "process terminated\n", NULL, NULL);
	return (0);
}
