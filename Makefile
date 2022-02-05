all:
	gcc -Wall -Wextra -Werror -Ilibft -lmlx -framework OpenGL -framework AppKit libft.a fractol.c -o bin