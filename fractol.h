/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:45:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/08 16:13:58 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <signal.h>
#include <math.h>

#define NMAX 200
#define	SIZE_X 1000
#define	SIZE_Y 1000

#define BERNSTEIN1 2295.0
#define BERNSTEIN2 3825.0
#define BERNSTEIN3 2167.5

#define ON_KEYDOWN 2
#define ON_KEYUP 3
#define ON_MOUSEDOWN 4
#define ON_MOUSEUP 5
#define ON_MOUSEMOVE 6
#define ON_EXPOSE 12
#define ON_DESTROY 17

typedef struct	s_bounds
{
	double	re_max;
	double	re_min;
	double	im_max;
	double	im_min;
	double	d_r;
	double	d_i;
}				t_bounds;

typedef struct	s_pixel
{
	int				x;
	int				y;
	int				color;
	struct s_pixel	*next;
}				t_pixel;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*im_ptr;
	void		*tmp_im_ptr;
	char		*addr;
	char		*tmp_addr;
	int			bpp;
	int			line_size;
	int			endian;
	int			s_width;
	int			s_height;
	int			im_width;
	int			im_height;
	t_bounds	*bounds;
}				t_mlx;

int	get_color(double t);
char	*mandelbrot(t_mlx *mlx, double r_min, double r_max, double i_max);

#endif