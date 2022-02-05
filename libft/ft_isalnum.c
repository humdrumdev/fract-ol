/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:57:37 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/01 13:58:54 by hel-moud         ###   ########.fr       */
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

static inline int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}
