/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:53:39 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/17 16:18:16 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "lst.h"
# include <stdarg.h>

int		print_type(va_list ap, t_conv_details *det, char type);
int		print_node(t_conv *conv, va_list ap);
int		check_for_errors(t_conv *conv);
int		handle_flag(char flag, char type, t_conv_details *det);
char	get_padding(t_conv_details *det);
int		normal_hex(int num, int len, t_conv_details *det, char *base);

#endif
