CC = gcc
FLAGS = -Wall -Werror -Wextra

NAME = miniRT.a

LIBMLX = libmlx.dylib \
		libmlx.a

$(NAME) = miniRT

$(LIBMLX) = libmlx

$(DYLIB) = $(LIBMLX).dylib

all:
	make -C ./minilibx_mms_20200219/
	make -C ./minilibx_opengl_20191021/

bonus:

clean:

fclean:

re:

.PHONY: all, clean, fclean, re, bonus
