all:
	gcc fractol.c server.c libft.a -o bin -Wall -Wextra -Werror -Ilibft -lm -lmlx -lXext -lX11 -g

# all:
# 	gcc -Wall -Wextra -Werror -Ilibft -lm -lmlx -framework OpenGL -framework AppKit libft.a fractol.c server.c -o bin