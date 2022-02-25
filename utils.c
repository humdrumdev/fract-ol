/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:19:04 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/25 22:04:22 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	swap_vp(void **a, void **b)
{
	void	*t;

	t = *a;
	*a = *b;
	*b = t;
}

void	put_next_frame(t_mlx *mlx)
{
	mlx->draw->draw(mlx);
	swap_vp((void **)&mlx->addr, (void **)&mlx->tmp_addr);
	swap_vp((void **)&mlx->im_ptr, (void **)&mlx->tmp_im_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->im_ptr, 0, 0);
}

void	show_use(t_mlx *mlx)
{
	if (mlx->args->w_shades)
		return ;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 10, DEF_COLOR, USAGE0);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 30, DEF_COLOR, USAGE1);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 50, DEF_COLOR, USAGE2);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 70, DEF_COLOR, USAGE3);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 90, DEF_COLOR, USAGE4);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 110, DEF_COLOR, USAGE5);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 130, DEF_COLOR, USAGE6);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 150, DEF_COLOR, USAGE7);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 170, DEF_COLOR, USAGE8);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, X_START, 190, DEF_COLOR, USAGE0);
}

double	compute_next_doublebrot(t_mlx *mlx, t_draw *vars)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = vars->r_z * vars->r_z;
	b = vars->i_z * vars->i_z;
	if (mlx->args->w_dist)
	{
		vars->tmp = vars->i_z;
		vars->tmp_p = vars->r_zp;
		c = vars->i_z * vars->r_z;
		d = (a * vars->r_zp - vars->r_zp * b - (c + c) * vars->i_zp);
		vars->r_zp = 1. + d + d + d;
		vars->i_zp = - (vars->i_zp * b + vars->i_zp * a);
		vars->i_zp += (c + c) * vars->tmp_p;
		vars->i_zp += vars->i_zp + vars->i_zp;
	}
	vars->i_z = (a + a + a - b) * vars->i_z + vars->i_c;
	vars->r_z = (a - (b + b + b)) * vars->r_z + vars->r_c;
	return (a + b);
}

double	compute_next_fract(t_mlx *mlx, t_draw *vars)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = vars->r_z * vars->r_z;
	b = vars->i_z * vars->i_z;
	c = vars->i_z * vars->r_z;
	if (mlx->args->w_dist)
	{
		vars->tmp = vars->i_z;
		d = vars->r_z * vars->r_zp;
		vars->tmp = vars->i_z * vars->i_zp;
		vars->tmp_p = vars->r_zp;
		vars->r_zp = (d + d - (vars->tmp + vars->tmp));
		vars->r_zp += (mlx->args->set == MANDELBROT);
		vars->tmp = vars->r_z * vars->i_zp;
		vars->tmp_p *= vars->i_z;
		vars->i_zp = (vars->tmp + vars->tmp_p + vars->tmp + vars->tmp_p);
	}
	vars->i_z = c + c + vars->i_c;
	vars->r_z = a - b + vars->r_c;
	return (a + b);
}
