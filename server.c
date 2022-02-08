/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:19:37 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/08 16:20:50 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// quasiperiodic colorization

#define INV_LOG2 1.44269504089
#define A 1.44269504089 // 1 / ln(2)
#define B 0.34004648219 // 1 / (ln(2) * 3 *sqrt(2))
#define C 0.41366809925 // 1 / (ln(2) * 7 * (3 ^ (1/8)))

#define RADIUS2 65536

int	get_periodic_color(double t)
{
	double	r;
	double	g;
	double	b;

	r = (1 - cos(A * t)) * 127.5;
	g = (1 - cos(B * t)) * 127.5;
	b = (1 - cos(C * t)) * 127.5;
	return ((int)floor(r) << 16 | (int)floor(g) << 8 | (int)floor(b));
}

int	get_color(double t)
{
	double	r;
	double	g;
	double	b;

	r = BERNSTEIN1 * (1.0 - t) * pow(t, 2.0);
	g = BERNSTEIN2 * pow(1.0 - t, 2.0) * pow(t, 2.0);
	b = BERNSTEIN3 * pow(1.0 - t, 3.0) * t;
	return ((int)floor(r) << 16 | (int)floor(g) << 8 | (int)floor(b));
}

char	*mandelbrot(t_mlx *mlx, double r_min, double r_max, double i_max)
{
	double	px_size;
	// double	px_size_y;
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

	img = NULL;
	if (free_alloc((void **)&img, SIZE_X * SIZE_Y * 4 + 1))
		return (NULL);
	px_size = (r_max - r_min) / SIZE_X;
	// px_size_y = (mlx->bounds->d_i) / SIZE_Y;
	line_width = (r_max - r_min) / SIZE_X;
	y = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			r_c = r_min + (x * px_size);
			i_c = i_max - (y * px_size);
			r_z = 0;
			i_z = 0;
			r_zp = 0;
			i_zp = 0;
			n = 0;
			powr = 1.;
			q = pow(r_c - 0.25, 2.) + i_c * i_c;
			if (q * (q + r_c - 0.25) < i_c * i_c * 0.25 || r_c * r_c + r_c + r_c + 1 + i_c * i_c < 0.0625)
				n = NMAX;
			while (n < NMAX)
			{
				tmp = (r_z * r_z) + (i_z * i_z);
				if (tmp > RADIUS2)
					break ;
				tmp = i_z;
				tmp_p = r_zp;
				r_zp = 1 + 2 * (r_z * r_zp - i_z * i_zp);
				i_zp = 2 * (r_z * i_zp + i_z * tmp_p);
				i_z = (i_z + i_z) * r_z + i_c;
				r_z = r_z * r_z - tmp * tmp + r_c;
				powr += powr;
				n++;
			}
			v = log(tmp) / powr;
			v = log(v) * INV_LOG2;
			// v = log(v) / 0.1;
			//good value 0.01 0.08 0.8 1 2 8 0.1 go bigger with zooms
			if (n == NMAX)
				d = 0;
			else
			{
				tmp = r_z * r_z + i_z * i_z;
				tmp_p = r_zp * r_zp + i_zp * i_zp;
				d = (sqrt(tmp) * log(tmp) / sqrt(tmp_p));
			}
			// *(int *)(img + y * mlx->line_size + 4 * x) = get_color((double)n / NMAX);
			// *(int *)(img + y * mlx->line_size + 4 * x) = (n == NMAX) ? 0 : get_color(sin(n));
			// *(int *)(img + y * mlx->line_size + 4 * x) = d < line_width ? 0 : get_color((double)n / NMAX);
			// *(int *)(img + y * mlx->line_size + 4 * x) = d < line_width ? 0 : 0x00FFFFFF;
			*(int *)(img + y * mlx->line_size + 4 * x) = d < line_width ? 0 : get_periodic_color(v);
			x++;
		}
		y++;
	}
	return (img[SIZE_X * SIZE_Y * 4] = '\0', img);
}