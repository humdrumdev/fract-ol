#### global
NAME:=libft.a
CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -O2
OBJ_DIR:=obj
ARFLAGS:=rcs
##end global

#### sources
#first

UTIL_FUNCS:=ft_absolutev.c ft_greater_than.c ft_is_equal.c ft_is_negative.c\
 ft_less_than.c ft_max.c ft_min.c ft_is_successor.c ft_bounded.c get_next_line.c free_alloc.c \
 clean_exit.c

FIRST:=ft_isalpha.c ft_memcmp.c  ft_strdup.c  ft_strnstr.c \
ft_atoi.c    ft_isascii.c ft_memcpy.c  ft_strlcat.c ft_strrchr.c \
ft_bzero.c   ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c \
ft_calloc.c  ft_isprint.c ft_memset.c  ft_strlen.c  ft_toupper.c \
ft_isalnum.c ft_memchr.c  ft_strchr.c  ft_strncmp.c ft_strcpy.c ft_strcmp.c

#second
SECOND:=ft_itoa.c  ft_putnbr_fd.c  ft_striteri.c  ft_strtrim.c \
ft_putchar_fd.c ft_putstr_fd.c  ft_strjoin.c  ft_substr.c \
ft_putendl_fd.c ft_split.c  ft_strmapi.c

#bonus
BONUS:=ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
	ft_lstmap.c ft_lstnew.c ft_lstsize.c

#all
SRC:=$(FIRST) $(SECOND) $(BONUS) $(UTIL_FUNCS)
##end sources

#### object
#first
FIRST_OBJ:=$(FIRST:.c=.o)
#second
SECOND_OBJ:=$(SECOND:.c=.o)
#bonus
BONUS_OBJ:=$(BONUS:.c=.o)
#utils
UTIL_OBJ:=$(UTIL_FUNCS:.c=.o)
#all
OBJ = $(FIRST_OBJ) $(SECOND_OBJ) $(BONUS_OBJ) $(UTIL_OBJ)
##end objects

#libftprintf
PRINTFDIR:=ft_printf
PRINTFSRC:=char.c decimal_di.c di_zero_left.c flags.c list_functions.c str.c conv.c di_left.c di_zero_normal.c \
ft_printf.c list_functions2.c u_int.c conv_handler.c di_normal.c di_zero_right.c hex_bx.c parser.c utils.c \
core.c di_right.c flag_handlers.c hex_x.c percent.c void_p.c
PRINTFHEADERS:=char.h core.h flags.h hex.h parser.h str.h utils.h \
conv_handler.h decimal_di.h ft_printf.h lst.h percent.h u_int.h void_p.h
HEADER_FILES=$(addprefix $(PRINTFDIR)/, $(PRINTFHEADERS)) libft.h
PRINTFSRC:=$(addprefix $(PRINTFDIR)/, $(PRINTFSRC))
PRINTFOBJ:=$(PRINTFSRC:.c=.o)
ALLSRC:=$(PRINTFSRC) $(SRC)
ALLOBJ:=$(PRINTFOBJ) $(OBJ)

#### compiling rules

.PHONY: all clean fclean re $(NAME)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(ALLSRC) $(HEADER_FILES)
	@$(MAKE) lib --no-print-directory

lib: $(ALLOBJ)
	ar $(ARFLAGS) $(NAME) $^

clean:
	rm -rf $(ALLOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
