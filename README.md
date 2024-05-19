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

