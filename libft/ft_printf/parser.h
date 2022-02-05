/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:48:51 by hel-moud          #+#    #+#             */
/*   Updated: 2021/12/17 20:44:33 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lst.h"
# include <stdlib.h>

# define TYPES "%cspdiuxX"
# define FLAGS "-0+ #"

t_conv	*new_node(t_beg_n_end beg_end[3], const char *format, char type);
t_conv	*new_simple_node(int beg, int end, const char *format);
char	*get_new_string(int beg, int end, const char *s);
int		add_back(t_conv **head, t_conv *new);
void	clear_list(t_conv **head);
void	delete_node(t_conv *node);
t_conv	*parse_format(const char *format);

#endif
