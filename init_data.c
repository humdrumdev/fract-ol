/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:26:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 20:11:18 by hel-moud         ###   ########.fr       */
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
		return (free_alloc(NULL, 0), NULL);
	new->win_ptr = mlx_new_window(new->mlx_ptr, im_width, im_height, title);
	if (!new->win_ptr)
		return (free(new->mlx_ptr), free_alloc(NULL, 0), NULL);
	new->addr = init_image(new, &new->im_ptr, im_width, im_height);
	if (!new->addr)
	{
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free_alloc(NULL, 0), NULL);
	}
	new->tmp_addr = init_image(new, &new->tmp_im_ptr, im_width, im_height);
	if (!new->tmp_addr)
	{
		mlx_destroy_image(new->mlx_ptr, new->im_ptr);
		mlx_destroy_window(new->mlx_ptr, new->win_ptr);
		return (free(new->mlx_ptr), free_alloc(NULL, 0), NULL);
	}
	return (new);
}

int	init_mlx_data(t_mlx *mlx)
{
	if (free_alloc((void **)&mlx->bounds, sizeof(t_bounds)))
		return (-1);
	if (free_alloc((void **)&mlx->def_bounds, sizeof(t_bounds)))
		return (free_alloc(NULL, 0), -1);
	if (free_alloc((void **)&mlx->draw, sizeof(t_draw)))
		return (free_alloc(NULL, 0), -1);
	mlx->bounds->re_max = 2.;
	mlx->bounds->re_min = -2.;
	mlx->bounds->im_max = 2.;
	mlx->bounds->im_min = -2.;
	mlx->bounds->d_r = 4.;
	mlx->bounds->d_i = 4.;
	ft_memcpy(mlx->def_bounds, mlx->bounds, sizeof(t_bounds));
	mlx->draw->img = NULL;
	mlx->coloriser = NULL;
	mlx->color_gen = INV_LOG2;
	mlx->im_height = 1000;
	mlx->im_width = 1000;
	mlx->j = -0.8;
	mlx->k = 0.156;
	mlx->def_j = -0.8;
	mlx->def_k = 0.156;
	mlx->event = 0;
	return (0);
}

void	init_listners(t_mlx *mlx)
{
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	mlx_mouse_hook(mlx->win_ptr, handle_mouse, mlx);
	mlx_hook(mlx->win_ptr, ON_DESTROY, 0, close_win, mlx);
}
