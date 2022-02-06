/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:19:37 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/06 15:39:22 by hel-moud         ###   ########.fr       */
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