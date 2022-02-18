/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:14:06 by hel-moud          #+#    #+#             */
/*   Updated: 2022/02/18 20:45:42 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_exit(int s_c, const char *msg, void (*clnr)(void **), void **mem)
{
	if (mem)
	{
		if (!clnr)
			free(*mem);
		else
			clnr(mem);
	}
	free_alloc(NULL, 0);
	ft_printf(msg);
	exit(s_c);
}
