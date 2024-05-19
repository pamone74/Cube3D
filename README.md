## My First RayCaster Using miniLibX
Before delving into the details, it's essential to ensure we have all the necessary resources at our disposal, particularly when working with C.<br>
have at out disposal and as usal, we use C.<br>
### 📎Let's make sure the miniLibx is installed and working properly.
According to the provided PDF guide, there are two options for obtaining miniLibX: either using the version available on the operating system (in this case, on an iMac) or acquiring it from its sources. I won't delve into the details here, as there are documentation resources available for both choices.<br>
- 🥇 If opting for the version from the source, refer to the instructions provided on this GitHub repository:(https://github.com/42Paris/minilibx-linux).
- 🥈 Additionally, you may find this documentation helpful for getting started: (https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#compilation-on-macos).

If minilibx is well obtained, then we can proceed.
Let me give you a glimpse of the steps we will take. I will try to make this topic more easy and user friendly and will i will start from beginning to the end. 
### Step One: Configuring the Map
If you have experience with the `so_long` project, these steps might be more familiar to you. However, for those like myself who haven't worked on `so_long`, extensive research was necessary to understand how to correctly insert maps.

#### Drawing Our 2D Map on the GPU
This step might seem redundant, but it is crucial for grasping what we are doing here and, more importantly, for understanding ray casting. As I couldn't find a straightforward method to draw lines using the MiniLibX library, I implemented Bresenham's line drawing algorithm to render the 2D map. I won't go into detail about the algorithm here, but you can learn more about it from this (https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/). 
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
```

Keep in mind that your map may differ from mine; currently, I've only drawn the walls, represented by `1`.

