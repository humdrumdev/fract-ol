/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:06:53 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/10 12:07:04 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*mandelbrot(t_mlx *mlx, t_color *coloriser, double color_gen);
char	*julia(t_mlx *mlx, t_color *coloriser, double color_gen);
char	*other(t_mlx *mlx, t_color *coloriser, double color_gen);

