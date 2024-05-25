## My First RayCaster Using miniLibX
Before delving into the details, it's essential to ensure we have all the necessary resources at our disposal, particularly when working with C

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
    But for better parsing, you may need to skip some empty spaces. You can use split() function, but later on, i will push the complete project later.
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
- 2️⃣  : Also Add this functions for drawing line in `utils.`c and you can add this to the header file `cube3D.h` `void ft_draw_2d_map(char **tilemap, void *mlx_ptr, void *win_ptr, int row)`
```C 
// ====================================== Draw Line Functions ===================================================================

/*
    Relax, you do not actaully needs this for submission unless otherwise: You may need this if you are planning for bonus, drawing mini map
    I wish i could explain this in simple term that you can unserstand. But if you know basic of math, that would be better.
    okay, i have variables:
        dx (change in x cordinates)
        dy (changes in y cordinates)

    Alright, let's break it down:

    In mathematics, when we talk about drawing a line between two points, we often use the equation of a straight line:  y = mx + c , where  m  
    is the slope of the line and  c  is the y-intercept. In the case of computer graphics, we're dealing with pixels on a screen, 
    so  we don't directly use this equation. Instead, we use discrete points to approximate the line.

    Here's how variables relate to this equation:
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
            recieved = ft_extract_map(argv, ac);
            char **mapp = recieved->map;
            int row = recieved->row;
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
🌟 **The small square visible represents our player**: In our map data we have `N` but this can either be `NWSE`, we'll later use the character for player's position from the map  and make player face that specific wall respectively . But for now, let's not worry about that detail. We're taking things step by step, from beginner's level to achieving perfection. It's crucial to thoroughly understand each step along the way.
   
![Screenshot from 2024-05-24 20-52-55](https://github.com/pamone74/Cube3D/assets/140634743/ba89bde2-0887-4656-9c28-cb61a3d20bd6)


### So now our 2D map is ok but the player is static. We do not need that.
***Here's what we are going to do next***:
- 🌓 Check map validity: At this point we need to make sure our map data is valid.
- 🌓 Event management: Using the `WASD` keys, arrow keys and destroy window
- 🌓 Wall collision
- 🌓 Ray tracing

## Map validity:
Alright i have created some basic functions to check for valid map:
- 🍮 Add these two funtions to `utils.c` and offcourse add the function prototype to the header file
  
**Copy this and paste it in `utils.c`**
```C
// ===================================== Validate the map =========================================================
// validate the map
int validate_map(char **map)
{
    size_t i = 0;
    int j = 0;
    size_t count_holder;
    // count the size of map, we can just pass the row.
    size_t count = 0;
    
    while(map[count])
        count++;
    count_holder = count;
    // printf("%ld\n", count);
    // check top and bottom rows
    while(i < strlen(map[j]) && --count_holder)
    {
        if(map[0][i] != '1' || map[count-1][i] != '1')
        {
            printf("Invalid map Wall not closed top and bottom\n");
            // printf("Invalid map 1 map[0][%ld] = %c map[%ld][%ld]) = %c\n", i, map[0][i] ,count-1,i, map[count-1][i]);
            return 0;
        }  
        i++;
        j++;
    }
    //  check left and right
    i = 0;
    while(i < count)
    {
        if(map[i][0] != '1' || map[i][strlen(map[i])-1] != '1')
        {
            printf("Invalid map Wall not closed left and right\n");
            return 0;
        }
        //  for whatever reason, it was not checking the last corner
        if (i == count -1)
        {
            if(map[i][0] != '1' || map[i][strlen(map[i])-1] != '1')
            {
                printf("Invalid map Wall not closed \n");
                return 0;
            }
        }
        i++;
    }
    return 1;
}
// checking for players position and invalid characters
int ft_validate_map(char **map)
{
    int i = 0;
    int flag = 0;
    while (map[i])
    {
       int j = 0;
       while(map[i][j])
       {
            if(strchr("NWSE", map[i][j]))
            {
                if(flag)
                {
                    printf("Players position cannot be more than one\n");
                    return 0;
                }
                else
                    flag = 1;
            }
            else if(!strchr("NWSE01", map[i][j]))
            {
                printf("Invalid Character found on the map %c pos = %d %d\n", map[i][j], i ,j);
                return 0;
            }
                
            j++;
       }
       i++;
    }
    return 1;
}

```
***Now its a good time to update our `test.c` we need to make sure the map is valid before even thinking of openning the window***
- update the `test.c`, add conditional if, and all the window related programs should be inside if block.
```C
 // check if the map is valid: if its is not valid no need to open the window
            // we should make sure that the mapp is not empty
            if (ft_validate_map(mapp) && validate_map(mapp) && mapp)
            {

            // Let's first configure to open our window

                mlx_int = mlx_init();
                img.img = mlx_new_image(mlx_int, WIDTH, HEIGHT);
                img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
                mlx_win = mlx_new_window(mlx_int, HEIGHT, WIDTH, "Cube 3D");
                ft_draw_2d_map(mapp, mlx_int, mlx_win, row);
                mlx_loop(mlx_int);
            }
            else
           {
		// here we can free all the memory that we have allocated either directly or indirectly then maybe we return. Lets save that for another time
                printf("oops not valid\n");
           }
```
***Let's manage the event***
At this point i believe you are familiar with the event. In mlx there are several ways we can manage the event. I will not go deep to explain even and whatsoever. I will include comments in the code explaining. 
## What is `WASD` keys?
The WASD keys are a set of four keys on a standard computer keyboard, often used as the primary movement controls in video games. They are typically mapped to movement in games where the mouse controls aiming. "W" typically moves the character or forward, "A" moves left, "S" moves backward, and "D" moves right. This configuration is popular because it allows for quick and efficient movement while still leaving the player's other hand free to use the mouse for aiming or other actions..

### Mlx Events
Events are actions tiggered when a user interacts with the keyboards, such as pressing, or releasing the keys. So handling the event is capturing the user's input and responding accordingly. 
- In mlx, we can use mlx_hook(win_ptr, x_event, mask, function_handler, param)
  	- 🌓 The parameter `x_event` represents the key of the event for example `02` is the key for `KeyPress` event.
  	  ***Frpm the picture below, notice the row for Key, those are the key for the events***

	![Screenshot from 2024-05-25 18-56-49](https://github.com/pamone74/Cube3D/assets/140634743/4f808ee6-8ec6-4bb9-b425-f7925f046107)

	- 🌓 The parameter `mask` specify the event mask. This way you can only register to only one event when it is triggered or to all keys if you leave your mask to default. 

 	 ![Screenshot from 2024-05-25 18-57-10](https://github.com/pamone74/Cube3D/assets/140634743/1a7aa0b8-61a8-4a3e-88ec-3a805d0da87a)

	- 🌓 The parameter `function_handler` specifies the function that will be called when the event is triggered. For example if we have used `02` and the mask of `1L<<0` for key press event, we can then use appropaite key event prototype for the key. if you look the prototype for `ON_KEYDOWN and ON_KEYUP` have same function prototye meaning we can use this prototyp to handle any kind of key event.

  
	![Screenshot from 2024-05-25 18-57-34](https://github.com/pamone74/Cube3D/assets/140634743/db437833-b866-4d76-9ca0-b1794f384dce)

***Alright Let's go ahead and hanlde the event***
To to this we need a function `ft_event_init(t_window *mlx)` 
- ℹ️ Before we go to far, i want you to know that i have modified and update some funtioons, i have added structs to the header and so to make our work easier, i will include the updated files here `utils.c` `test.c` and `cube3d.h` I have included comments for every changes i have made. you can unserstand more from the comments.
- Alright let me first talk about how i hanlde the event and manage to let `WASD` keys to work

  ### Check the screen shot below.
  
  ![Screenshot from 2024-05-25 19-50-18](https://github.com/pamone74/Cube3D/assets/140634743/3c77d9a0-e49f-4203-a9f1-49188c1cd7ac)

  ***By using the above infomation, we can then control the players movement effectively.***
  - I have `ft_event_init` function that will call `mlx_hook`
 ```C
	void ft_event_init(t_window *mlx)
	{
   
    		if (mlx->mlx_win)
			// Key Event
        		mlx_hook(mlx->mlx_win, 02, 1L << 0, ft_key_handle,mlx);
	}
  ```
  - check out the function handler below for KEY press event:
  ```C
	int ft_key_handle(int keyssys, t_window *mlx)
	{
	    // i will create struct for these variable later on
 	   double sin_a = sin(PLAYER_ANGLE);
 	   double cos_a = cos(PLAYER_ANGLE);
	   double dx = 0.0;
 	   double dy = 0.0;
	   double speed_sin = sin_a * PLAYER_SPEED;
  	   double speed_cos = cos_a * PLAYER_SPEED;
	    // if your are not sure about the KEY, just print the keyssys for every key you press then you will know the value. 
	    // Keep in mind that these key values are never the same
	    // escape key
	    if (keyssys == 65307)
  	      exit(0);
	    // W key
	    else if(keyssys == 119)
	    {
	        dx += speed_cos;
 	       dy += speed_sin;
	    }
	    // A
	    else if(keyssys == 97)
	    {
	        dx += speed_sin;
	        dy -= speed_cos;
	    }
	    // S
	    else if(keyssys == 115)
	    {
	        dx += -speed_cos;
	        dy += -speed_sin;
	    }
	    // D 
	    else if(keyssys == 100)
	    {
	        dx += -speed_sin;
	        dy += speed_cos;
	    }
	    mlx->player_pos_x += dx;
	    mlx->player_pos_y += dy;
	    // left key
	    if (keyssys == 65361)
	        mlx->player_angle -= PLAYER_ROT_SPEED;
	    // Right Key
	    if (keyssys == 65363)
	        mlx->player_angle += PLAYER_ROT_SPEED;
	    mlx->player_angle = fmod(mlx->player_angle, 2 * PI);
	    if (mlx->player_angle < 0)
	        mlx->player_angle += 2 * PI; // Ensure angle is positive
	    // For every key we press the player's position needs to be update, i do not kmow if clearing the window is the best thing to do but i will update as i go along
	    mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	    ft_render(mlx);
	    return 0;
	
	}

  ```

## Now Let's update the files we have already `test.c`, `cube3d.h` and `utils.c`
# cube3d.h

```C
#ifndef CUBE3D_H
#define CUBE3D_H
#define HEIGHT 800
#define WIDTH 600

#include  <stdlib.h>
#include <mlx.h>
#include <math.h>

// Map information

// tile
#define TILE_SIZE 50

// Players settings
#define PLAYER_ANGLE 0  // Now Let's say when the game starts, the player angle should be 0;
#define PLAYER_SPEED 1  // we could have used 0.005 * time delta, unfortunately we cannot use time.h here
#define PLAYER_ROT_SPEED 1
#define PLAYER_SIZE_SCALE 15


// MATH
#define PI 3.14159265358979323846


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
    int row; // This is the number of row of the map
}t_map_data;

typedef struct s_wind{
    void *mlx_ptr;
    void *mlx_win;
    double player_pos_x;
    double player_pos_y;
    int player_angle;
    t_data image;
    t_map_data *map_data;

}t_window;



//========= utils.c ===================
t_map_data* ft_extract_map(char **argv, int ac);
int validate_map(char **map);
int ft_validate_map(char **map);


// Draw 2D
void ft_draw_2d_map(char **tilemap, t_window *mlx, int row);

// Events
void ft_event_init(t_window *mlx_win);
int ft_key_handle(int keyssys, t_window *mlx);

// Init
void ft_game_init(t_window *mlx);

// Render
void ft_render(t_window * mlx);

// Data initi
void ft_data_init(t_window *mlx);
#endif
```

# Test.c
```C
#include "cube3D.h"
#include <stdio.h>

int main(int ac, char *argv[])
{
    if (ac == 2)
    {
        t_window mlx;
        char *map = argv[1];
        if (map)
        {
            mlx.map_data = ft_extract_map(argv, ac);
            if (ft_validate_map(mlx.map_data->map) && validate_map(mlx.map_data->map) && mlx.map_data->map)
            {
                ft_game_init(&mlx);
                ft_render(&mlx);
                mlx_loop(mlx.mlx_ptr );
            }
            else
                printf("oops not valid\n");
    

           
        }
    }
}
```

# utils.c
```C
#include "./mlx/cube3D.h"
#include "./mlx/get_next_line/get_next_line.h"
#include "./mlx/libft/libft.h"
#include <unistd.h>

// ======================================================================= Extract Map data ====================================================================================
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


//===================================================================================  validate the map ================================================================================

int validate_map(char **map)
{
    size_t i = 0;
    int j = 0;
    size_t count_holder;
    // count the size of map, we can just pass the row.
    size_t count = 0;
    
    while(map[count])
        count++;
    count_holder = count;
    while(i < strlen(map[j]) && --count_holder)
    {
        if(map[0][i] != '1' || map[count-1][i] != '1')
        {
            printf("Invalid map Wall not closed top and bottom\n");
            return 0;
        }  
        i++;
        j++;
    }
    //  check left and right
    i = 0;
    while(i < count)
    {
        if(map[i][0] != '1' || map[i][strlen(map[i])-1] != '1')
        {
            printf("Invalid map Wall not closed left and right\n");
            return 0;
        }
        //  for whatever reason, it was not checking the last corner
        if (i == count -1)
        {
            if(map[i][0] != '1' || map[i][strlen(map[i])-1] != '1')
            {
                printf("Invalid map Wall not closed \n");
                return 0;
            }
        }
        i++;
    }
    return 1;
}

// ============================================================= checking for players position and invalid characters ====================================================================

int ft_validate_map(char **map)
{
    int i = 0;
    int flag = 0;
    while (map[i])
    {
       int j = 0;
       while(map[i][j])
       {
            if(strchr("NWSE", map[i][j]))
            {
                if(flag)
                {
                    printf("Players position cannot be more than one\n");
                    return 0;
                }
                else
                    flag = 1;
            }
            else if(!strchr("NWSE01", map[i][j]))
            {
                printf("Invalid Character found on the map %c pos = %d %d\n", map[i][j], i ,j);
                return 0;
            }
                
            j++;
       }
       i++;
    }
    return 1;
}


// ====================================== Draw Line Functions ===================================================================

/*
    Relax, you do not actaully needs this for submission unless otherwise
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
void draw_line(t_window *mlx,int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1-x0);
    int dy = -abs(y1-y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;
    while(1)
    {
        mlx_pixel_put(mlx->mlx_ptr, mlx->mlx_win, x0, y0, color);
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

void draw_rect(t_window *mlx, int x, int y, int size, int color)
{
    draw_line(mlx, x, y, x + size , y, color); // top side
    draw_line(mlx, x, y, x  , y+ size, color); // left side
    draw_line(mlx, x + size, y, x+ size  , y + size , color); // right side
    draw_line(mlx, x, y + size , x + size , y+ size, color); // bottom side
}

void ft_draw_2d_map(char **tilemap, t_window *mlx, int row)
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
               draw_rect(mlx, y * TILE_SIZE, x*TILE_SIZE, TILE_SIZE, 0x0000FF00);  
        
            y++;
        }
        x++;
    }
}



// ================================================= Event Handler =====================================================

void ft_event_init(t_window *mlx)
{
   
    if (mlx->mlx_win)
        mlx_hook(mlx->mlx_win, 02, 1L << 0, ft_key_handle,mlx);
}

int ft_key_handle(int keyssys, t_window *mlx)
{
    // i will create struct for these variable later on
    double sin_a = sin(PLAYER_ANGLE);
    double cos_a = cos(PLAYER_ANGLE);
    double dx = 0.0;
    double dy = 0.0;
    double speed_sin = sin_a * PLAYER_SPEED;
    double speed_cos = cos_a * PLAYER_SPEED;
    // if your are not sure about the KEY, just print the keyssys for every key you press then you will know the value. 
    // Keep in mind that these key values are never the same
    // escape key
    if (keyssys == 65307)
        exit(0);
    // W key
    else if(keyssys == 119)
    {
        dx += speed_cos;
        dy += speed_sin;
    }
    // A
    else if(keyssys == 97)
    {
        dx += speed_sin;
        dy -= speed_cos;
    }
    // S
    else if(keyssys == 115)
    {
        dx += -speed_cos;
        dy += -speed_sin;
    }
    // D 
    else if(keyssys == 100)
    {
        dx += -speed_sin;
        dy += speed_cos;
    }
    mlx->player_pos_x += dx;
    mlx->player_pos_y += dy;
    // left key
    if (keyssys == 65361)
        mlx->player_angle -= PLAYER_ROT_SPEED;
    // Right Key
    if (keyssys == 65363)
        mlx->player_angle += PLAYER_ROT_SPEED;
    mlx->player_angle = fmod(mlx->player_angle, 2 * PI);
    if (mlx->player_angle < 0)
        mlx->player_angle += 2 * PI; // Ensure angle is positive
    // For every key we press the player's position needs to be update, i do not kmow if clearing the window is the best thing to do but i will update as i go along
    mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
    ft_render(mlx);
    return 0;

}



// ============================================================ Render the window ===============================================================

/*
    This function is pretty simple, we need to draw out 2d map, player's position, players driection. simple
*/
void ft_render(t_window * mlx)
{
    char **tilemap = mlx->map_data->map;
    int row = mlx->map_data->row;
    ft_draw_2d_map(tilemap, mlx, row); // Draw the 2D map once

    // This is the player's position
    draw_rect(mlx, mlx->player_pos_y , mlx->player_pos_x, PLAYER_SIZE_SCALE, 0x00FF0000);

    // Drawing line for the players's driection
    draw_line(mlx, mlx->player_pos_y, mlx->player_pos_x, mlx->player_pos_y + WIDTH * cos(mlx->player_angle), mlx->player_pos_x + WIDTH * sin(mlx->player_angle), 0x000000FF);
}




// ========================================================== Init function ===================================================================

/*
    We need to intialize our window, this is just familiar things: but if its your first time with mlx then you need to unserstand it.
    Well , follow the inline comment, you will understand what i am doing there.

*/
void ft_game_init(t_window *mlx)
{
    // initialize the window server
    mlx->mlx_ptr = mlx_init();
    if(mlx->mlx_ptr == NULL)
    {
        printf("Malloc erro\n");
        exit(EXIT_FAILURE);
    }
    // window
    // i want my image to be displayed horizontally so i will use height fot width and width for height
    mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, HEIGHT, WIDTH, "CUBE 3D");
    if (!mlx->mlx_win)
    {
        free(mlx->mlx_ptr);
        printf("Malloc error \n");
        exit(EXIT_FAILURE);
    }
    // img ptr;
    // i want my image to be displayed horizontally so i will use height fot width and width for height
    // it should be like this mlx->image.img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT); but .......
    mlx->image.img = mlx_new_image(mlx->mlx_ptr, HEIGHT, WIDTH);
    if(mlx->image.img == NULL)
    {
        mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
        free(mlx->mlx_ptr);
        printf("Malloc Error\n");
        exit(EXIT_FAILURE);
    }
    mlx->image.addr = mlx_get_data_addr(mlx->image.img, &mlx->image.bits_per_pixel, &mlx->image.line_length, &mlx->image.endian);
    ft_data_init(mlx);
    ft_event_init(mlx);
    
}


// ============================================================ Get player's coordinates x and y ==================================================================
void ft_data_init(t_window *mlx)
{
    int x = 0;
    char **map = mlx->map_data->map;
    while(x < mlx->map_data->row)
    {
        int y = 0;
        while(y < (int)strlen(map[x]))
        {
            if (strchr("NSEW", map[x][y]))
            {
                mlx->player_pos_x = x * TILE_SIZE;
                mlx->player_pos_y = y *TILE_SIZE;
            }
            y++;
        }
        x++;
    }
}
```


# Next this is checking wall collison 
