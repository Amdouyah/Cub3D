NAME = cub3D

NAMEBONUS = cub3DBonus

CC = gcc

FLAG = -framework Cocoa -framework OpenGL -framework IOKit 

CFLAGS = -Wall -Wextra -Werror -I cub3d.h

SRC = main.c  hooks.c math.c hooks1.c color.c raycast.c raycast2.c\
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

SRCBONUS = ./bonus/mainbonus.c \
	./bonus/hooks_bonus.c \
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

OBJBONUS = $(SRCBONUS:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ)
	cd libft && make
	$(CC) $(CFLAGS)  $(FLAG)  /Users/amdouyah/Desktop/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/amdouyah/.brew/opt/glfw/lib/" $(SRC) -o $(NAME) ./libft/libft.a

clean :
	@rm -rf $(OBJ) $(OBJBONUS)
	cd libft && make clean

fclean : clean
	@rm -rf $(NAME)  $(NAMEBONUS)
	cd libft && make fclean

re : fclean all 

bonus : $(OBJBONUS)
	cd libft && make
	$(CC) $(CFLAGS) -fsanitize=address $(FLAG) /Users/amdouyah/Desktop/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/amdouyah/.brew/opt/glfw/lib/" $(SRCBONUS) -o $(NAMEBONUS) ./libft/libft.a