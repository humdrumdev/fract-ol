/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:45:38 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 19:17:25 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "libft.h"

/*
** useful constants
** 1 / ln(2)
** 1 / (ln(2) * 3 * sqrt(2))
** 1 / (ln(2) * 7 * (3 ^ (1/8)))
*/

#define INV_LOG2 1.44269504089
#define A 1.44269504089
#define B 0.34004648219
#define C 0.41366809925

#define BERNSTEIN1 2295.0
#define BERNSTEIN2 3825.0
#define BERNSTEIN3 2167.5

#define MANDELBROT 1
#define JULIA 2
#define DOUBLEBROT 3

/*
** usage
*/

#define USAGE0 "####################################################\n"
#define USAGE1 "# move left, right, up and down using the arrows   #\n"
#define USAGE2 "# zoom in and out using the mouse wheel            #\n"
#define USAGE3 "# control the depth of the fractal using (+ and -) #\n"
#define USAGE4 "# control the color shades using (* and /)         #\n"
#define USAGE5 "# change the coloring using ENTER                  #\n"
#define USAGE6 "# change the julia set using right click           #\n"
#define USAGE7 "# go back to default using middle click            #\n"

#define BIN_USAGE "usage : %s <fractal name> [optional : enhanced (-e)] [optional: gradient coloring (-c)]\n"
/*
** keys
*/

#ifdef __APPLE__

#define ON_DESTROY 17

#define UP 126
#define DOWN 125
#define LEFT 123
#define RIGHT 124

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 3
#define SCROLL_UP 4
#define SCROLL_DOWN 5

#define ESC 53
#define PLUS 69
#define MINUS 78
#define DIVIDE 75
#define MULTIPLY 67
#define ENTER 36

#define CTRL 256
#define KEY_C 8

#elif __linux__

#define ON_DESTROY 17

#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 3
#define MOUSE_MIDDLE 2
#define SCROLL_UP 4
#define SCROLL_DOWN 5

#define ESC 65307
#define PLUS 61
#define MINUS 45
#define DIVIDE 249
#define MULTIPLY 42
#define ENTER 65293

#define CTRL 65507
#define KEY_C 99

#endif

#define DEF_COLOR 0x009400D3
#define X_START 10

#define TERNARY(CND, X, Y) ((CND) ? (X) : (Y))

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

t_mlx	*new_mlx(int im_width, int im_height, char *title);
int		init_mlx_data(t_mlx *mlx);
int		update_image(t_mlx *mlx, bool new);
void	put_next_frame(t_mlx *mlx);
void	show_use(t_mlx *mlx);
void	init_listners(t_mlx *mlx);
void	shift(t_mlx *mlx, int direction);
void	zoom(t_mlx *mlx, int direction, int x, int y);
void	swap_vp(void **a, void **b);
double	compute_next_doublebrot(t_mlx *mlx, t_draw *vars);
double	compute_next_fract(t_mlx *mlx, t_draw *vars);
int		colorize(t_mlx *mlx, t_draw *vars);
int		get_color(double t);
int		get_periodic_color(double t);
void	draw(t_mlx *mlx);
int		change_julia(int x, int y, t_mlx *mlx);
int		handle_mouse(int button, int x, int y, t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);
char	*init_image(t_mlx *mlx, void **img, int im_width, int im_height);
void	colorise_pixel(t_mlx *mlx, t_draw *vars);
int		close_win(t_mlx *mlx);

#endif
