/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:45:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/16 22:44:35 by hel-moud         ###   ########.fr       */
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
#include <stdbool.h>
#include <assert.h>

// #define RADIUS2 65536 //(2 ^ 16)

// #define NMAX 200 //previously 200
// #define	SIZE_X 1000
// #define	SIZE_Y 1000

#define INV_LOG2 1.44269504089
#define A 1.44269504089 // 1 / ln(2)
#define B 0.34004648219 // 1 / (ln(2) * 3 *sqrt(2))
#define C 0.41366809925 // 1 / (ln(2) * 7 * (3 ^ (1/8)))

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

#define UP 126
#define DOWN 125
#define LEFT 123
#define RIGHT 124

#define MANDELBROT 1
#define JULIA 2
#define DOUBLEBROT 3

#define CM1 1
#define CM2 2
#define CM3 3

#define TERNARY(C, X, Y) (C ? X : Y)

typedef struct	s_region
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int	offset;
}				t_region;

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

typedef int (*t_color)(double);

typedef void (*t_drawf)();

typedef struct	s_draw
{
	t_drawf	draw;

	double	px_size;
	double	line_width;
	double	r_z;
	double	i_z;

	double	r_zp;
	double	i_zp;

	double	r_c;
	double	i_c;

	double	tmp;
	double	tmp_p;

	double	d;
	double	powr;
	double	v;
	double	q;

	char	*img;
	int		x;
	int		y;
	int		n;
}				t_draw;

typedef struct s_args
{
	int		set;
	bool	w_dist;
	bool	w_shades;
}				t_args;

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

	int			im_width;
	int			im_height;

	double		j;
	double		k;
	double		def_j;
	double		def_k;

	t_bounds	*bounds;
	t_bounds	*def_bounds;
	double		color_gen;
	t_color		coloriser;
	int			color_mode;
	t_draw		*draw;
	int			event;
	int			n_max;
	int			radius_sq;
	t_args		*args;
	int			px_move;
}				t_mlx;

void	put_next_frame(t_mlx *mlx);
void	init_listners(t_mlx *mlx);
void	shift(t_mlx *mlx, int direction);
void	zoom(t_mlx *mlx, int direction, int x, int y);
void	swap_vp(void **a, void **b);
int		colorize(t_mlx *mlx, t_draw *vars);
int		get_color(double t);
int		get_periodic_color(double t);
void	draw(t_mlx *mlx);

int		change_julia(int x, int y, t_mlx *mlx);
int		handle_mouse(int button, int x, int y, t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);
void	interupt_handler(int signum);
char	*init_image(t_mlx *mlx, void **img, int im_width, int im_height);

void	colorise_pixel(t_mlx *mlx, t_draw *vars);

#endif
