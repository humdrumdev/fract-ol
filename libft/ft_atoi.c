/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:07:11 by hel-moud          #+#    #+#             */
/*   Updated: 2021/12/10 20:16:56 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline int	is_space(char c)
{
	int	cnd;

	cnd = ((c == ' ') || (c == '\n') || (c == '\t'));
	return (cnd || (c == '\v') || (c == '\r') || (c == '\f'));
}

static inline int	is_num(char c)
{
	return ((c >= '0') && (c <= '9'));
}

static int	to_num(const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (is_num(str[i]))
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	issign;
	int	sign;

	i = 0;
	while (is_space(str[i]))
		i++;
	sign = 1;
	issign = ((str[i] == '+') + (str[i] == '-'));
	if (issign)
	{
		i++;
		sign *= issign;
	}
	if ((str[i] == '+') + (str[i] == '-'))
		return (0);
	return (sign * to_num(str + i));
}
