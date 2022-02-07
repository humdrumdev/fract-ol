/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bounded.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:33:48 by hel-moud          #+#    #+#             */
/*   Updated: 2022/01/07 20:14:36 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_bounded(int lhs, int num, int rhs)
{
	return (lhs <= num && rhs >= num);
}