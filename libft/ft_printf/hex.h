/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:51:34 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:45:32 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEX_H
# define HEX_H

# include "lst.h"
# include <stdarg.h>

int	print_x(va_list ap, t_conv_details *det);
int	print_bx(va_list ap, t_conv_details *det);

#endif
