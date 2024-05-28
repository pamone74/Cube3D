// #include "./mlx_linux/mlx.h"
#include "cube3D.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>             

int tilemap[HEIGHT][WIDTH] ={
   { 1, 1, 1, 1, 1, 1, 1, 1,1, 1 },
   { 1, 0, 0, 0, 1, 0, 0, 0,0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0,0, 1 },
   { 1, 0, 0, 1, 0, 0, 0, 0,0, 1 },
   { 1, 0, 0, 1, 1, 0, 0, 0,0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0,0, 1 },
   { 1, 0, 0, 1, 0, 0, 0, 0,0, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1,1, 1 },
};
int validate(int tilemap[HEIGHT][WIDTH])
{
    int i = 0;
    // check top and bottom rows
    while(i < 10)
    {
        if(tilemap[0][i] != 1 || tilemap[8-1][i] != 1)
        {
            return 0;
        }  
        i++;
    }
    //  check left and right
    i = 0;
    while(i < 8)
    {
        if(tilemap[i][0] != 1 || tilemap[i][10-1] != 1)
        {
            return 0;
        }
        i++;
    }
    return 1;
}
int validate_map(int tilemap[HEIGHT][WIDTH]){
    int i = 0;
    while (i < HEIGHT)
    {
       int j = 0;
       while(j < WIDTH)
       {
            if(tilemap[i][j] != 1 || tilemap[i][j] != 0)
                return 0;
            j++;
       }
       i++;
    }
    return 1;
}

int ft_gettile(int x, int y){
    return tilemap[y][x];
}

void ft_settiletype(int x,int y, int type)
{
    tilemap[y][x] = type;
}

// void my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char *dst;
//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel/8));
//     *(unsigned int *)dst = color;
// }
// void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
// {
//     int dx = abs(x1-x0);
//     int dy = -abs(y1-y0);
//     int sx = x0 < x1 ? 1 : -1;
//     int sy = y0 < y1 ? 1 : -1;
//     int err = dx + dy;
//     int e2;
//     while(1)
//     {
//         mlx_pixel_put(mlx, win, x0, y0, 0x0000FF00);
//         if (x0 == x1 && y0 == y1)
//             break;
//         e2 = 2 * err;
//         if(e2 >= dy)
//         {
//             err += dy;
//             x0 += sx;
//         }
//         if (e2 <= dx)
//         {
//             err += dx;
//             y0 += sy;
//         }
//     }

// }

// void draw_rect(void *mlx, void * win, int x, int y, int size)
// {
//     draw_line(mlx, win, x, y, x + size , y);
//     draw_line(mlx, win, x, y, x  , y+ size);
//     draw_line(mlx, win, x + size, y, x+ size  , y + size );
//     draw_line(mlx, win, x, y + size , x + size , y+ size );
// }
// void ft_draw_2d_map(void *mlx_ptr, void *win_ptr)
// {
//     int x;
//     int y;
//     x = 0;

//     while(x < 8)
//     {
//         y = 0;
//         while(y < 10)
//         {
//             if(tilemap[x][y] == 1)
//             {
//                draw_rect(mlx_ptr, win_ptr,x * 50, y*50, 50);
//             }
//             y++;
//         }
//         x++;
//     }
// }

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;
    mlx = mlx_init();
    printf("I amhere");
    img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_win = mlx_new_window(mlx, HEIGHT, WIDTH, "Cube 3D");
    printf("I amhere");
    //ft_draw_2d_map(mlx, mlx_win);
    // mlx_put_image_to_window(mlx,mlx_win,img.img,10, 10);
    mlx_loop(mlx);
    

}