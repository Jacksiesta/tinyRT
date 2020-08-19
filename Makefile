CC = gcc
FLAGS = -Wall -Werror -Wextra
NAME = miniRT
MLX = minilibx/libmlx.a
MLX_FLAGS = -L minilibx -lmlx -framework OpenGL -framework AppKit
INCLUDES = includes/miniRT.h\
		includes/sphere.h\
		includes/vector.h\
		includes/canvas.h\
		includes/light.h\
		includes/lstobjects.h\
		includes/raytracing.h\
		includes/get_next_line.h

SRC_PATH = srcs
SRC_NAME = miniRT.c \
		sphere.c \
		canvas.c \
		light.c \
		raytracing.c \
		vector_math.c \
		vector_color.c \
		vector.c \
		lstobjects.c \
		utils/get_next_line.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(INCLUDES) $(OBJS) $(MLX)
		$(CC) $(FLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX) :
		make -C minilibx all

clean :
		rm -f srcs/$(OBJS)

fclean :	clean
		rm -f $(NAME)

re: fclean all
