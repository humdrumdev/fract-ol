/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_p.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:46:56 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:47:13 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOID_P_H
# define VOID_P_H

# include "lst.h"
# include <stdarg.h>

int	print_ptr(va_list ap, t_conv_details *det);

#endif
