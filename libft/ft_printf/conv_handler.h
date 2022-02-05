/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:31:02 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/27 18:15:01 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_HANDLER_H
# define CONV_HANDLER_H

# include <stdarg.h>
# include "lst.h"

t_conv_details	*conv_handler(t_conv *conv, va_list ap);

#endif
