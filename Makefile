NAME =		cub3D
GNL = get_next_line
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = 	./srcs
MLX_DIR = 	./mlx_linux
OBJS_DIR =	./objs
GNL_DIR = GNL
LIBFT_DIR = ./Libft

CC =		clang -g -fsanitize=address
FLAGS_CC =	-Wall -Wextra -Werror
FLAGS_MLX =	-lm -lbsd -lX11 -lXext -lmlx
FLAGS_LIBFT = -lft
			
MLX =		$(MLX_DIR)/libmlx.a
SRCS =		$(SRC_DIR)/main.c\
			$(SRC_DIR)/first_steps.c\
			$(SRC_DIR)/player_move.c\
			$(SRC_DIR)/initial_check.c\
			$(SRC_DIR)/map_setup.c\
			$(SRC_DIR)/map_resolution.c\
			$(SRC_DIR)/map_color.c\
			$(SRC_DIR)/map_texture.c\
			$(SRC_DIR)/map_map.c\
			$(SRC_DIR)/close.c\
			$(SRC_DIR)/ft_render.c\
			$(SRC_DIR)/ft_draw_line.c\
			$(GNL_DIR)/get_next_line.c\
			$(GNL_DIR)/get_next_line_utils.c

HEAD =		-I ./$(SRC_DIR) -I ./$(GNL_DIR) -I ./$(LIBFT_DIR) -L ./$(LIBFT_DIR) -I ./$(MLX_DIR) -L ./$(MLX_DIR)

OBJS =		$(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS)) #subst in directory

RM =		/bin/rm -rf

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS) #$@ means the output file will be ./cub3D instead of ./a.out
	$(CC) $(FLAGS_CC) $(OBJS) $(HEAD) $(FLAGS_MLX) $(FLAGS_LIBFT) -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(HEAD) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make re -C $(LIBFT_DIR)

clean:
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

run: re
	./cub3D $(ARGS)

debug: $(MLX) $(OBJS)
	$(CC) -g $(FLAGS_MLX) $(FLAGS_CC) $(OBJS) $(HEAD) $(MLX) -o "cub3D_debug"

.PONY: all clean fclean re