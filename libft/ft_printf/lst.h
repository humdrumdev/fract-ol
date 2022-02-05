/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 04:29:52 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/27 18:20:03 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

typedef struct s_begin_n_end
{
	int	start;
	int	end;
	int	is_zero;
}				t_beg_n_end;

typedef struct s_conv_details
{
	int	is_zero_padded;
	int	is_hash_padded;
	int	is_sign_padded;
	int	is_space_padded;
	int	is_padded_to_left;
	int	is_padded_to_right;
	int	is_precisioned;
	int	precision;
	int	min_width;
	int	is_zeroed;
	int	has_blank;
	int	len;
}				t_conv_details;

typedef struct s_conv
{
	char			*flags;
	char			*width;
	char			*precision;
	char			type;
	struct s_conv	*next;
}					t_conv;

#endif
