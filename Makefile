NAME = cub3d

LIBFT = libft.a

PATH_GNL = ./gnl/

PATH_LIBFT = ./Libft/

PATH_MLX = ./mlx_linux/

PATH_SRCS = ./srcs/

SRCS = main.c\
	first_steps.c\
	player_move.c

OBJS = $(addprefix $(PATH_SRCS),$(SRCS:.c=.o))

FLAGS = -Wall -Wextra -Werror
FLAGS_MLX = -lm -lX11 -lXext -lbsd

CC = gcc -g $(FLAGS)

.c.o:
	gcc -g $(FLAGS) -I$(PATH_GNL) -I$(PATH_LIBFT) -I$(PATH_MLX) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PATH_LIBFT)
	$(CC) $(OBJS) -L$(PATH_LIBFT) -lft -I$(PATH_LIBFT) -L$(PATH_MLX) -lmlx -I$(PATH_MLX) $(FLAGS_MLX) -o $(NAME)

clean:
	make clean -C $(PATH_LIBFT)
	rm -rf $(OBJS)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all