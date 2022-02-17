all:
	gcc colors.c draw.c main.c drawing.c scale.c event_listeners.c libft.a -o bin -Wall -Wextra -Werror -Ilibft -lm -lmlx -lXext -lX11 -g

# all:
# 	 gcc -Wall -Wextra -Werror -Ilibft -lm -lmlx -framework OpenGL -framework AppKit libft.a colors.c draw.c main.c drawing.c scale.c event_listeners.c -o bin