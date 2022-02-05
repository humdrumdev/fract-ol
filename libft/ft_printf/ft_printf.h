/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:54:49 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:44:48 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

# include "../libft.h"
# include "char.h"
# include "conv_handler.h"
# include "core.h"
# include "decimal_di.h"
# include "flags.h"
# include "hex.h"
# include "lst.h"
# include "parser.h"
# include "percent.h"
# include "str.h"
# include "u_int.h"
# include "utils.h"
# include "void_p.h"

void			init_conv_details(t_conv_details *det);
int				flag_handler(char type, char *flags, t_conv_details *det);
t_conv_details	*conv_handler(t_conv *conv, va_list ap);
int				print_type(va_list ap, t_conv_details *det, char type);
int				print_node(t_conv *conv, va_list ap);
int				ft_printf(const char *format, ...);

#endif
