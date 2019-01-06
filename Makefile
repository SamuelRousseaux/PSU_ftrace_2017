##
## EPITECH PROJECT, 2018
## strace
## File description:
## makefile
##

CC	= gcc

RM	= rm -f

NAME	= ftrace

SRC	=	src/main.c		\
		src/list_sym_tab.c	\
		src/sym_tab_funcs.c	\
		src/syscall.c		\
		src/trace.c

OBJ	=$(SRC:.c=.o)

ifeq ($(DEBUG),1)
CFLAGS	+= -g3 -ggdb
endif

CFLAGS	+= -W -Wall -Wextra -I./inc -lelf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
