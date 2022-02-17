all:
	gcc colors.c draw.c main.c drawing.c scale.c event_listeners.c libft.a -o bin -Wall -Wextra -Werror -Ilibft -lm -lmlx -lXext -lX11 -g

# all:
# 	 gcc -Wall -Wextra -Werror -Ilibft -lm -lmlx -framework OpenGL -framework AppKit libft.a colors.c draw.c main.c drawing.c scale.c event_listeners.c -o bin

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif