NAME := fractol
LIBDIR := libft
LIB := libft.a
CC := gcc
FLAGS := -Wall -Wextra -Werror -O2 -I$(LIBDIR)
CFLAGS := $(FLAGS) -lm -lmlx -framework OpenGL -framework AppKit
ifeq ($(shell uname -s),Linux)
CFLAGS := $(FLAGS) -lm -lmlx -lXext -lX11
endif
SRC := colors.c draw.c event_listeners.c handlers.c scale.c drawing.c init_data.c utils.c
OBJ := $(SRC:.c=.o)

%.o : %.c fractol.h
	$(CC) $(FLAGS) -c $< -o $@

all: $(LIB) $(OBJ) fractol.h
	$(CC) $(CFLAGS) main.c $(OBJ) $(LIB) -o $(NAME)

$(NAME) : all

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME) $(LIB)
re : fclean all

$(LIB):
	@$(MAKE) -C $(LIBDIR) --no-print-directory
	mv $(LIBDIR)/$(LIB) $(LIB)
	@$(MAKE) -C $(LIBDIR) fclean --no-print-directory
