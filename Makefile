NAME = cub3D

NAMEBONUS = cub3DBonus

CC = gcc

FLAG = -framework Cocoa -framework OpenGL -framework IOKit 

CFLAGS = -Wall -Wextra -Werror -O3 -I  cub3d.h

SRC = main.c  hooks.c math.c hooks1.c color.c raycast.c raycast2.c sec_main.c\
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

SRCBONUS = ./bonus/main_bonus.c ./bonus/hooksbonus.c ./bonus/mathbonus.c ./bonus/hooks1bonus.c ./bonus/colorbonus.c ./bonus/raycastbonus.c ./bonus/raycast2bonus.c\
	./get_next_line/get_next_line.c \
	./get_next_line/get_next_line_utils.c \
	./bonus/parsing/tools.c \
	./bonus/parsing/parsing.c \
	./bonus/parsing/more_tools.c \
	./bonus/parsing/checking_tx.c \
	./bonus/parsing/checking_map.c \
	./bonus/parsing/checking_cl.c \
	./bonus/parsing/f_more_tools.c \
	./bonus/parsing/parsing_func.c \
	./bonus/sec_main.c \
	./bonus/hooks_con.c \

OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ)
	cd libft && make
	$(CC)  $(CFLAGS)  $(FLAG)  /Users/amdouyah/Desktop/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/amdouyah/.brew/opt/glfw/lib/" $(SRC) -o $(NAME) ./libft/libft.a

clean :
	@rm -rf $(OBJ) $(OBJBONUS)
	@make clean -C ./libft

fclean : clean
	@rm -rf $(NAME)  $(NAMEBONUS)
	@make fclean -C ./libft

re : fclean all 

bonus : $(OBJBONUS)
	cd libft && make
	$(CC)  $(CFLAGS)  $(FLAG) /Users/amdouyah/Desktop/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/amdouyah/.brew/opt/glfw/lib/" $(SRCBONUS) -o $(NAMEBONUS) ./libft/libft.a