/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:11:14 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/01 14:11:52 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static inline int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
