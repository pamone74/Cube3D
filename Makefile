NAME = cube3D
FLAG = -Wall -Wextra -Werror
CFLAGS = cc
SRC = tezt.c utils.c
OBJ = $(SRC:.c=.o)

# Path to mlx_linux directory relative to mlx directory
MLX_PATH = ./mlx_linux
GNL_PATH = ./get_next_line

all: $(NAME)

%.o: %.c
	$(CFLAGS) $(FLAG) -I/usr/include -I$(MLX_PATH) -O3 -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MLX_PATH)
	$(CFLAGS) $(OBJ) -L$(MLX_PATH) ./mlx_linux/libmlx.a  -L/usr/usr/lib ./mlx_linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME) $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c

clean: 
	make clean -C $(MLX_PATH)
	rm -f $(OBJ)
fclean:
	rm -f $(NAME)

re: clean fclean all

