NAME = cub3D

CC = gcc

FLAG = -framework Cocoa -framework OpenGL -framework IOKit 

CFLAGS = -Wall -Wextra -Werror -I  cub3d.h

SRC = main.c \
	./get_next_line/get_next_line.c \
	./get_next_line/get_next_line_utils.c \
	./parsing/tools.c \
	./parsing/parsing.c \
	./parsing/more_tools.c \
	./parsing/checking_tx.c \
	./parsing/checking_map.c \
	./parsing/checking_cl.c \
	./parsing/f_more_tools.c \
	./parsing/parsing_func.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cd libft && make
	$(CC) $(CFLAGS) $(FLAG) /Users/amdouyah/Desktop/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/amdouyah/.brew/opt/glfw/lib/" $(SRC) -o $(NAME) ./libft/libft.a

clean :
	@rm -rf $(OBJ)
	cd libft && make clean

fclean : clean
	@rm -rf $(NAME)
	cd libft && make fclean

re : fclean all 