#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd, size_t size)
{
	char	*line;
	char	*tmp;
	int		total;

	if ((line = (char *)malloc(size)))
	{
		total = 0;
		while (read(fd, line + total, 1) == 1 && line[total++] != '\n');
		if (!total)
			return (free(line), NULL);
		line[total] = '\0';
		tmp = line;
		if ((line = (char *)malloc(total)))
		{
			while ((*line++ = *tmp++));
			return (free(tmp - total - 1), line - total - 1);
		}
		return (free(tmp), NULL);
	}
	return (line);
}

int	main()
{
	int		fd;
	// char	*line;

	// fd = open("Makefile", O_RDONLY);
	// while ((line = get_next_line(fd, 1000)))
	// 	(printf("%s", line), free(line));
	// close(fd);
	return (0);
}