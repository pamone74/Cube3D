## My First RayCaster Using miniLibX
Before delving into the details, it's essential to ensure we have all the necessary resources at our disposal, particularly when working with C.<br>
have at out disposal and as usal, we use C.<br>
### There are these terms I might be using frequently so get familiar with it:
- **Protagonist**: The main character in a game. Let me say a player's character. 
- **FOV**: Field of View
- **FPS**: First Person Shooter. This genre of games allows players to experience the action through the eyes of the protagonist. While it often involves combat or shooting elements, it isn't exclusively about shooting. Think about your perspective right now as you look at your monitor; this is your Field of View (FOV). Your FOV is essentially what your camera sees. Now, imagine you're playing a game where you can only see your character's hands in front of you. This is because the game's camera is positioned as if it were your own eyes, providing a highly immersive experience.

## Take a look at this picture, This is FPS perspective
![FPS](https://github.com/pamone74/Cube3D/assets/140634743/68bf0437-dc8d-46f5-8844-c57d689b8d36)

### simple explanation of FOV and FPS
In an FPS game, the player's perspective is crucial as it directly influences the gameplay experience. The Field of View (FOV) determines how much of the game world is visible on the screen at any given moment, impacting the player's spatial awareness and immersion.

When creating an FPS game with ray casting, understanding and properly setting up the FOV is essential for realistic rendering and gameplay mechanics. The FOV needs to be wide enough to provide a good view of the surroundings but not so wide that it distorts the perspective.


  
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
 #### I strongly suggest that you follow along with my code so that we stay on the same track.
- First of all, this is how my files are organized:
  - `mlx`
    - `libft`
    - `get_next_line`
    - `mlx_linux`
    - `Makefile`
    - `*.c`
    - `.cub`
    - `.h`


  
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
  		int row;
	}t_map_data;

	typedef struct s_player{
    		int player_pos_x;
    		int player_pos_y;
    		char player_view;

	}t_player;


	// utils.c | Later on we shall be adding some funcions here
	#endif
  ```
### Makefile [Linux Environment]
-  Please note that as of now, when i am writing this doc, i am using linux evn, but the configuration for the Mac OS, i will update it soon.
```Makefile

NAME = cube3D
FLAG = -Wall -Wextra -Werror
CFLAGS = cc
SRC = test.c utils.c
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
- To keep this document simple and user-friendly, we will use just two `.c` files: `test.c` and `utils.c`.
- Note that I'm not strictly following coding norms here, and this is not the final version.
- Before proceeding, please add the two `.c` files to the root directory of `mlx`.
- `test.c` will be used for testing, while `utils.c` will contain functions for our cube3D.

### Here is the map I will use to illustrate and demonstrate the process:
Please note that this is a basic map, and I am assuming it is correct with no errors (meaning no need for parsing). However, in reality, you must parse the map.
- Add a file named `map1.cub` to the root directory of `mlx` and paste the complete map metadata.
  ```
	NO path_to/wall1.xpm
	SO path_to/wall2.xpm
	EA path_to/wall3.xpm
	WE path_to/wall4.xpm

	F 255,0,0
	C 0,0,255

	11111111111111
	10010000000001
	1000000N000011
	11000010000001
	10000010000001
	10000000010001
	10001000010001
	10000000000001
	10000000000001
	10000000000001
	11111111111111
  ```
### Explanation of the Map Metadata
- ➡️ `NO`: This specifies the texture path for the North wall. The texture should be in `.xpm` format. Replace `path_to` with the actual path where your texture is located. For example, if you have a directory named `img` and have stored your textures for the North wall there, replace `path_to` with the exact file path.
- ➡️ Similarly, `SO` is for the South wall, `EA` is for the East wall, and `WE` is for the West wall.
- ➡️ `F` specifies the color of the floor, and `C` specifies the color of the ceiling.
- ➡️ The `1` represents a wall, and `0` represents empty space. Characters `N`, `W`, `E`, and `S` on the map indicate the player's position and initial facing direction. For example, if the character `N` is used, when the game starts, the player will face the North wall, meaning the player's Field of View (FOV) is towards the North wall. The same logic applies to the other characters.
  
#### Drawing Our 2D Map on the GUI or window
This step might seem redundant, but it is crucial for grasping what we are doing here and, more importantly, for understanding ray casting. As I couldn't find a straightforward method to draw lines using the MiniLibX library, I implemented Bresenham's line drawing algorithm to render the 2D map. I won't go into detail about the algorithm here, but you can learn more about it from this (https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/). 

- 1️⃣  : In the `utils.c` file, add this function for extracting the mapdata. Please not that this is absolutely not effecient function but, it will do what we need for now. And add function prototype to the header file
`t_map_data* ft_extract_map(char *argv, int ac)`
```C
// ================================================ Extracting map data ===================================================================
/*

    Please note that this is not effecient way of extracting map data, as i am assuming that everything is fine with the map: 
    But for better parsing, you may need to skip some empty spaces. You can use split() function, but later on, i will psuh the complete project later.
*/
t_map_data* ft_extract_map(char **argv, int ac)
{
    t_map_data *memory;
    memory = malloc(sizeof(t_map_data));
    if (!memory)
        return 0;
    if(ac == 2)
    {
        char *line = 0;
        int fd = open(argv[1],O_RDONLY);
        if(fd == -1)
            return 0;
        int i = 0;
        // to get the actual size we can allocate for the map, we may need to know  the row and column (r * c)
        // for now i am assuming that the size of row and column is 100: Absolutely it not recomended, it is not good approach to allocate the memory. 
        memory->map = malloc(sizeof(char *) * 100);
        if(!memory->map)
            return 0;
        while(1)
        {
            line = get_next_line(fd);
            // As you can notice, i am using strdup() this is beacuse i am freeing the line * in every iteration meaning that i will have null so to maintain it
            // we need to duplicate the value.
            if(line && strncmp(line, "NO", 2) == 0)
                memory->NO = strdup(line);
            if(line && strncmp(line, "SO", 2) == 0)
            // we can add more for the textures here
                memory->SO = strdup(line);
            if(line && strncmp(line, "F", 1) == 0)
                memory->color_floor = atoi(strdup(line+2));
            if(line && line[0] == 49)  
            {
                char **splted = ft_split(ft_strdup(line), '\n');
                memory->map[i++] = splted[0];
                memory->row += 1;

            }
                
            free(line);
            if(!line)
                break;
        }
        close(fd);
        return memory;
    }
    return 0;
}
```
- 2️⃣  : Also Add this functions for drawing line in `utils.`c and ou can add this to the header file `cube3D.h` `void ft_draw_2d_map(char **tilemap, void *mlx_ptr, void *win_ptr, int row)`
```C 
// ====================================== Draw Line Functions ===================================================================

/*
    Relax, you do not actaully needs this for submission unless otherwise: You may need this if you are planning for bonus, drawing mini map
    I wish i could explain this in simple term that you can unserstand. But if you know basic of math, that would be better.
    okay, i hvae variables:
        dx (change in x cordinates)
        dy (changes in y cordinates)

    Alright, let's break it down:

    In mathematics, when we talk about drawing a line between two points, we often use the equation of a straight line:  y = mx + c , where  m  
    is the slope of the line and  c  is the y-intercept. In the case of computer graphics, we're dealing with pixels on a screen, 
    so  we don't directly use this equation. Instead, we use discrete points to approximate the line.

    Here's how yvariables relate to this equation:
    -  dx  represents the change in the x-coordinates of the two points, which is analogous to the change in the x-values of the equation.
    -  dy  represents the change in the y-coordinates of the two points, which is analogous to the change in the y-values of the equation.
    So, if we were to write the slope  m  using these variables, it would be  m = dy/dx.
    In the code,  dx  is calculated as  x1 - x0 , which indeed gives us the change in x-coordinates. Similarly,  dy  is calculated as  y1 - y0 , 
    giving us the change in y-coordinates.
    So, in terms of our line equation,  dx  represents the horizontal distance between the starting and ending points, and  dy  represents the vertical 
    distance between them. These are essential for determining how we should draw the line.

    Understanding these changes helps us decide how to incrementally move from one pixel to another to accurately represent the line between the two given points 
    on the screen.
*/
void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1-x0);
    int dy = -abs(y1-y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;
    while(1)
    {
        mlx_pixel_put(mlx, win, x0, y0, 0x0000FF00);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if(e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }

}
/*
    I am drawing the rectangle using the line function i have created earlier. The size its like the measurment of the tile.
*/

void draw_rect(void *mlx, void * win, int x, int y, int size)
{
    draw_line(mlx, win, x, y, x + size , y);
    draw_line(mlx, win, x, y, x  , y+ size);
    draw_line(mlx, win, x + size, y, x+ size  , y + size );
    draw_line(mlx, win, x, y + size , x + size , y+ size );
}

void ft_draw_2d_map(char **tilemap, void *mlx_ptr, void *win_ptr, int row)
{
    int x;
    int y;
    x = 0;
    
    while(x < row)
    {
        y = 0;
        while(y < (int)strlen(tilemap[x])) 
        {
            if(tilemap[x][y] == '1')
            {
                //printf("%c", tilemap[x][y]);
                // printf("cord (x = %d, y = %d)\n", x, y);

               draw_rect(mlx_ptr, win_ptr,y * 50, x*50, 50); 
               // I am sca.ling the x and y cordinates by 50, and giving tile size to be 50, you can chose according to your needs, but mind that it should be relative to 
               //you screen width and height ese it will overflow. 
            }
            else if (strchr("NSEW", tilemap[x][y]))
            {
               // player's position
                draw_rect(mlx_ptr, win_ptr,y * 50, x*50, 10);
            }
            y++;
        }
        x++;
    }
}
```
- 3️⃣ : Once all components are functioning properly, we can proceed to test our 2D map. To do this, add the following main function to the file test.c. If you don't have a test.c file, create one. Before continuing, ensure you're familiar with MiniLibX by referring to the documentation provided here (https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#compilation-on-macos).

```C
#include "cube3D.h"
#include <stdio.h>

int main(int ac, char *argv[])
{
    if (ac == 2)
    {
        t_map_data * recieved;
        char *map = argv[1];
        // window;
        // mlx_init
        void *mlx_int;
        void *mlx_win;
        // mlx_win = 0;
        t_data img;
        if (map)
        {
            // int i = 0;
            recieved = ft_extract_map(argv, ac);
            char **mapp = recieved->map;
            int row = recieved->row;
            // printf("%d\n", row);
            // while(mapp[i])
            //     printf("%s\n", mapp[i++]);
            // printf("\n");
            // int validate = ft_validate_map(mapp);
            // printf("%d", validate);

            // Let's first configure to open our window

            mlx_int = mlx_init();
            img.img = mlx_new_image(mlx_int, WIDTH, HEIGHT);
            img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
            mlx_win = mlx_new_window(mlx_int, HEIGHT, WIDTH, "Cube 3D");
            ft_draw_2d_map(mapp, mlx_int, mlx_win, row);
            mlx_loop(mlx_int);
    

           
        }
    }
}
```
#### This is the screen shot of how our 2D map should look like:
If you follow each steps well., you should be able to see something like this. 
- ⭐ **the small quare you see, is our player**: Later on, in our map data we indicate N, meaning the player should face North wall, relax for now, we shall get there. Again as i said earlier, we are starting from beginners level to perfect work meaning we need to underatand each steps well. 
![Screenshot from 2024-05-24 20-52-55](https://github.com/pamone74/Cube3D/assets/140634743/ba89bde2-0887-4656-9c28-cb61a3d20bd6)


### So now our 2D map is ok but the player is static. We do not need that.
## Here's what we are going to do next:
- 🌓 Check map validity: At this point we neet to make sure our map data is valid.
- 🌓 Event management: Using the WASD keys, arrow keys and destroy window
- 🌓 Wall collision
- 🌓 Ray tracing

## Map validity:
Alright i have created some basic functions to check for valid map:
**Copy this and paste it in `utils.c`
```C
```
