NAME := fractol
LIBDIR := libft
LIB := libft.a
TH := -lpthread
CC := gcc
FLAGS := -Wall -Wextra -Werror -O2 -I$(LIBDIR) $(TH)
CFLAGS := $(FLAGS) -lm -lmlx -framework OpenGL -framework AppKit
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CFLAGS := $(FLAGS) -lm -lmlx -lXext -lX11
endif
SRC := colors.c draw.c event_listeners.c handlers.c scale.c drawing.c init_data.c utils.c
OBJ := $(SRC:.c=.o)

%.o : %.c fractol.h
	$(CC) $(FLAGS) -c $< -o $@

ifeq ($(UNAME_S),Linux)
all: $(LIB) $(OBJ) fractol.h
	$(CC) $(OBJ) main.c $(LIB) $(CFLAGS) -o $(NAME)
else
all: $(LIB) $(OBJ) fractol.h
	$(CC) $(CFLAGS) main.c $(OBJ) $(LIB) -o $(NAME)
endif

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
