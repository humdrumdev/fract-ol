/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:19:37 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/07 18:33:12 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	char	*img;
	int		x;
	int		y;
	int		n;

	img = NULL;
	if (free_alloc((void **)&img, mlx->im_width * mlx->im_height * 4 + 1))
		return (NULL);
	px_size = (r_max - r_min) / SIZE_X;
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
			while (n < NMAX)
			{
				if ((r_z * r_z) + (i_z * i_z) > 4)
					break ;
				tmp = i_z;
				tmp_p = r_zp;
				r_zp = 1 + 2 * (r_z * r_zp - i_z * i_zp);
				i_zp = 2 * (r_z * i_zp + i_z * tmp_p);
				i_z = (i_z + i_z) * r_z + i_c;
				r_z = r_z * r_z - tmp * tmp + r_c;
				n++;
			}
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
			*(int *)(img + y * mlx->line_size + 4 * x) = d < line_width ? 0 : get_color((double)n / NMAX);
			x++;
		}
		y++;
	}
	return (img[mlx->im_width * mlx->im_height * 4] = '\0', img);
}