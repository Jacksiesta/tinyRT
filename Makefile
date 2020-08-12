CC = gcc
FLAGS = -Wall -Werror -Wextra

DIR_HEADERS = ./includes/

DIR_SRCS = ./srcs/

DIR_OBJS = ./

LIBMLX = libmlx.dylib \
		libmlx.a

SRC = sphere.c \

SRCS = $(addprefix $(DIR_SRCS), $(SRC))

OBJS = $(SRC:.c=.o)
	INCLUDE = mlx.h

NAME = miniRT

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./minilibx_mms_20200219/
	make -C ./minilibx_opengl_20191021/
	cp ./minilibx_mms/libmlx.dylib libmlx.dylib
	cp ./minilibx_opengl/libmlx.a libmlx.a
	$(CC) $(FLAGS) -I $(DIR_HEADERS) $(LIBMLX) $(OBJS) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -o $@ $<
	@echo "Compiled "$<" successfully!"
	
clean:
	make -C $(LIBMLX) clean
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBMLX)/miniRT.a

re: fclean all

