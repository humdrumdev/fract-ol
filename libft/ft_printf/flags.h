/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:55:49 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:44:02 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# include "lst.h"

int	handle_hash(char type, t_conv_details *det);
int	handle_zero(char type, t_conv_details *det);
int	handle_minus(char type, t_conv_details *det);
int	handle_space(char type, t_conv_details *det);
int	handle_plus(char type, t_conv_details *det);
int	handle_flag(char flag, char type, t_conv_details *det);
int	flag_handler(char type, char *flags, t_conv_details *det);

#endif
