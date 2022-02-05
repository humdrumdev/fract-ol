/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <hel-moud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:22:55 by hel-moud          #+#    #+#             */
/*   Updated: 2021/12/08 20:46:11 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc_buf(char *p_buf, int p_size, int is_done)
{
	char	*buf;
	int		i;

	if (is_done)
	{
		buf = (char *)malloc(p_size * sizeof(char));
		if (!buf)
			return (NULL);
		i = -1;
		while (++i < p_size - 1)
			buf[i] = p_buf[i];
		buf[i] = '\0';
		return (buf);
	}
	buf = (char *)malloc((p_size + BUFFER_SIZE) * sizeof(char));
	if (!buf && p_buf)
		return (free(p_buf), buf);
	if (!buf || !p_buf)
		return (buf);
	i = -1;
	while (++i < p_size)
		buf[i] = p_buf[i];
	return (free(p_buf), buf);
}

static t_reader	init_reader(void)
{
	t_reader	reader;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	reader = (t_reader)malloc(sizeof(struct s_reader));
	if (!reader)
		return (NULL);
	reader->buf = alloc_buf(NULL, 0, 0);
	if (!reader->buf)
		return (free(reader), NULL);
	reader->bytes = 1;
	return (reader);
}

static void	free_reader(t_reader reader)
{
	if (reader)
	{
		if (reader->buf)
			free(reader->buf);
		free(reader);
	}
}

static char	*get_single_line(t_reader reader, int fd, int bytes)
{
	int				status;
	char			*ret;

	while ("not reached EOF or new line")
	{
		while (reader->buf[reader->bytes - 1] != '\n' && bytes < BUFFER_SIZE)
		{
			status = read(fd, reader->buf + reader->bytes, 1);
			if (status <= 0)
				break ;
			reader->bytes++;
			bytes++;
		}
		if (status == -1)
			return (free_reader(reader), NULL);
		if (status == 0 || reader->buf[reader->bytes - 1] == '\n')
		{
			ret = alloc_buf(reader->buf, reader->bytes + 1, 1);
			return (free_reader(reader), ret);
		}
		reader->buf = alloc_buf(reader->buf, reader->bytes, 0);
		if (!reader->buf)
			return (free(reader), NULL);
		bytes = 0;
	}
}

char	*get_next_line(int fd)
{
	t_reader	reader;

	reader = init_reader();
	if (!reader)
		return (NULL);
	if (read(fd, reader->buf, 1) <= 0)
		return (free_reader(reader), NULL);
	return (get_single_line(reader, fd, 1));
}
