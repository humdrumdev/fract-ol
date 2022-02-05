/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_di.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:18:57 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/16 22:42:52 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECIMAL_DI_H
# define DECIMAL_DI_H

# include <stdarg.h>
# include "lst.h"

int		print_di_zero(int len, t_conv_details *det, char special);
int		print_di_left(int len, t_conv_details *det, int num);
int		print_di_right(t_conv_details *det, int num);

int		print_di_zero_left(t_conv_details *det, char special);
int		print_di_zero_right(t_conv_details *det, char special);
int		di_zero_cases(t_conv_details *det, int len, char special);

int		di_right_case1(int slen, t_conv_details *det, int num);
int		di_right_case2(int num, int prec, int slen, t_conv_details *det);
void	di_right_case3_prec(int num, t_conv_details *det, int prec);
int		di_right_case3(int width, int num, t_conv_details *det, int prec);
void	di_right_general(int num, t_conv_details *det, int prec, int slen);

int		print_di_left_case1(int num, int len, int slen, t_conv_details *det);
int		di_left_prec(int num, int len, t_conv_details *det);
int		di_left_width(int num, int len, t_conv_details *det);

int		di_normal_case1(int slen, int width, int num);
int		di_normal_case2(int num, int prec, int slen);
int		di_normal_case3(int width, int num, int slen, int prec);

int		print_d_or_i(va_list ap, t_conv_details *det);

#endif
