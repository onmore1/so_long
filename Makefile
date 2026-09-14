NAME    := so_long

SRCS    := so_long.c Utils/utils.c Utils/coin_utils.c Map/check_map.c Map/create_map.c Map/tiles.c \
           Game/keys.c Game/render.c Game/init.c Bonus/Animations/coin_anim.c Map/check_map_2.c

LIBFT_DIR := libft
LIBFT     := $(LIBFT_DIR)/libft.a
MLX_DIR   := MLX42
MLX_LIB   := $(MLX_DIR)/build/libmlx42.a
MLX_INC   := -I $(MLX_DIR)

OBJS    := $(SRCS:.c=.o)
CC      := cc
CFLAGS  := -Wall -Wextra -Werror $(MLX_INC)
LIBS    := $(LIBFT) $(MLX_LIB) -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(OBJS) $(LIBS) -o $@

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "MLX42 not found, cloning..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@cmake -B $(MLX_DIR)/build $(MLX_DIR)
	@cmake --build $(MLX_DIR)/build -j4

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJS): %.o: %.c $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean re
