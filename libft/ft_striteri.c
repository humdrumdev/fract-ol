/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:14:31 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/04 11:12:49 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*func)(unsigned int, char *))
{
	int	i;

	if (s && func)
	{
		i = -1;
		while (s[++i])
			(*func)(i, s + i);
	}
}