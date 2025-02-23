CC = gcc
FLAGS = -Wall -Werror -Wextra
NAME = miniRT
MLX = minilibx/libmlx.a
MLX_FLAGS = -L minilibx -lmlx -framework OpenGL -framework AppKit -fsanitize=address
INCLUDES = includes/miniRT.h\
		includes/sphere.h\
		includes/vector.h\
		includes/canvas.h\
		includes/light.h\
		includes/lighting.h\
		includes/scene.h\
		includes/lstobjects.h\
		includes/raytracing.h\
		includes/intersect.h\
		includes/parsing.h\
		includes/plan.h\
		includes/square.h\
		includes/triangle.h\
		includes/cylinder.h\
		includes/camera.h\
		includes/utils.h\
		includes/get_next_line.h

SRC_PATH = srcs
SRC_NAME = miniRT.c \
		scene/camera.c \
		scene/canvas.c \
		scene/cylinder.c \
		scene/light.c \
		scene/lstobjects.c \
		scene/plan.c \
		scene/scene.c \
		scene/sphere.c \
		scene/square.c \
		scene/triangle.c \
		math/rotation.c \
		math/vector.c \
		math/vector_color.c \
		math/vector_math.c \
		parsing/parsing.c \
		parsing/parsing_obj.c \
		lighting.c \
		raytracing.c \
		reflect.c \
		intersect.c \
		utils/atoi.c \
		utils/leaks.c \
		utils/get_next_line.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(INCLUDES) $(OBJS) $(MLX)
		$(CC) $(FLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX) :
		make -C minilibx all

clean :
		rm -f $(OBJS)

fclean :	clean
		rm -f $(NAME)

re: fclean all
