## My First RayCaster Using miniLibX
Before delving into the details, it's essential to ensure we have all the necessary resources at our disposal, particularly when working with C.<br>
have at out disposal and as usal, we use C.<br>
### 📎Let's make sure the miniLibx is installed and working properly.
According to the provided PDF guide, there are two options for obtaining miniLibX: either using the version available on the operating system (in this case, on an iMac) or acquiring it from its sources. I won't delve into the details here, as there are documentation resources available for both choices.<br>
- 🥇 If opting for the version from the source, refer to the instructions provided on this GitHub repository:(https://github.com/42Paris/minilibx-linux).
- 🥈 Additionally, you may find this documentation helpful for getting started: (https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#compilation-on-macos).

Please Note: My goal is to make simplest doc, how we can achive 3D from 2D using ray casting. If you follow every steps carefully, i am pretty sure you can implement and understands it fully and most of the functions we will use here, you may end up not needing them in the final project, so it is fine even if it does not follow the norms. 

### Step One: Configuring the Map
If you have experience with the `so_long` project, these steps might be more familiar to you. However, for those like myself who haven't worked on `so_long`, extensive research was necessary to understand how to correctly insert maps.
- 🗺️ The map will be a file with a `.cub` extension, which will be passed as a command-line argument, for example, `.cube3D map.cub`.
- 🗺️ Parsing the map involves various terminologies and concepts, but I won't focus on parsing details right now. You can check my repository for the complete work. For now, let's get started with the basic concepts of cube3D and, most importantly, raycasting.
- 🗺️ There are specific rules to follow when parsing the map. However, as mentioned, I won't delve deeply into map parsing at this point. I'll update the parsing details later. For now, let's leave it as it is.
  #### I strongly suggest that you follow along my codes so that we stay on the same track.
  - First of all, this is how my files are organized:
  - mlx
      - libft
      - get_next_line
      - mlx_linux
      - Makefile
      - *.c
      - .cub
      - .h
  
  ## My header file cube3D.h
  ```C
	#ifndef CUBE3D_H
	#define CUBE3D_H
	#define HEIGHT 800
	#define WIDTH 600

	// Map information
	#define WALL 1
	#define EMPTY 0
	#define NORTH N
	#define SOUTH S
	#define EAST E 
	#define WEST W 

	#include  <stdlib.h>
	typedef struct s_data{
    		void *img;
    		char *addr;
    		int bits_per_pixel;
    		int line_length;
    		int endian;
	}   t_data;


	typedef struct s_map_meta_data{
    		char *NO; // North texture
  		char *SO; // South texture
    		char *EA; // East texture
    		char *WE; // West texture
    		int color_floor;
    		int color_cieling;
    		char **map;
	}t_map_data;

	typedef struct s_player{
    		int player_pos_x;
    		int player_pos_y;
    		char player_view;

	}t_player;


	// utils.c Later on we shall be adding some funcions here
	#endif
  ```
### Makefile [Linux Environment]
-  Please note that as of now, when i am writing this doc, i am using linux evn, but the configuration for the Mac OS, i will update it soon.
```Makefile

NAME = cube3D
FLAG = -Wall -Wextra -Werror
CFLAGS = cc
SRC = tezt.c utils.c
OBJ = $(SRC:.c=.o)

# Path to mlx_linux directory relative to mlx directory
MLX_PATH = ./mlx_linux
GNL_PATH = ./get_next_line
LIBFT_PATH = ./libft

all: $(NAME)

%.o: %.c
	$(CFLAGS) $(FLAG) -I/usr/include -I$(MLX_PATH) -O3 -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MLX_PATH)
	make -C $(LIBFT_PATH)
	$(CFLAGS) $(OBJ) -L$(MLX_PATH) ./mlx_linux/libmlx.a  -L/usr/usr/lib ./mlx_linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME) $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c $(LIBFT_PATH)/libft.a

clean: 
	make clean -C $(MLX_PATH)
	rm -f $(OBJ)
fclean:
	rm -f $(NAME)

re: clean fclean all


```

#### Drawing Our 2D Map on the GUI or window
This step might seem redundant, but it is crucial for grasping what we are doing here and, more importantly, for understanding ray casting. As I couldn't find a straightforward method to draw lines using the MiniLibX library, I implemented Bresenham's line drawing algorithm to render the 2D map. I won't go into detail about the algorithm here, but you can learn more about it from this (https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/). 
### This is the map i will be  using to illustrate and demonstrate the porocess:
// map here
```C 
void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
{
  int dx = abs(x1 - x0); // Change in x
  int dy = -abs(y1-y0); // change in y
  int sx = x0 < x1 ? 1 : -1; // If the starting x coordinate is less than the ending x coordinate, move right (1), otherwise move left (-1).
  int sy = y0 < y1 ? 1 : -1; //  If the starting y coordinate is less than the ending y coordinate, move down (1), otherwise move up (-1).
  int err = dx + dy; // is the error term used to determine when to increment the y coordinate
  int e2;
  while (1) {
    mlx_pixel_put(game->mlx, game->win, x0, y0, 0x0000FF00); // draws a pixel at the current coordinates (x0, y0) with the specified color.
    if (x0 == x1 && y0 == y1) break; // checks if the current coordinates have reached the endpoint. If so, the loop breaks.
    e2 = 2 * err; // calculates the doubled error term to compare against dx and dy
    if (e2 >= dy) {
        err += dy;
        x0 += sx;
    }
    if (e2 <= dx) {
        err += dx;
        y0 += sy;
    }
}
}

// draw rectangle
void draw_rect(void *mlx, void *win, int x, int y, int size)
{
// size is the tile. Lets say we have square tile, then we use that size to draw the rect
  draw_line(mlx, win, x,y,x + size, y);
  draw_line(mlx, win, x,y,x, y + size);
  draw_line(mlx, win, x + size,y,x + size, y + size);
  draw_line(mlx, win, x,y + size,x + size, y + size);
}

// Now we draw our 2D map using this function:
void draw_2d_map(t_data data, void *mlx_ptr, void *win_ptr)
{
  int x = 0;
  int y;
  // The map is in 2D, with row and column, where row is the height and width is the column. So this loop  will loops through the map:
  while(i < width)
  {
    y =0;
    while(y < height)
    {
      if(tilemap[x][y]) == 1
        draw_rect(mlx_ptr, win_ptr, x * 50, 50); // I have decided to give the tile size of 50
      y++;
    }
    i++;
  }
  
}
```

Keep in mind that your map may differ from mine; currently, I've only drawn the walls, represented by `1`.

