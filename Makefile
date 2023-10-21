NAME = cub3D

CC = gcc

FLAG = -framework Cocoa -framework OpenGL -framework IOKit 

CFLAGS = #-Wall -Wextra -Werror -I  cub3d.h

SRC = main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)

	$(CC) $(CFLAGS) -fsanitize=address -g $(FLAG) /Users/amdouyah/Desktop/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/amdouyah/.brew/opt/glfw/lib/" main.c -o $(NAME)

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all 