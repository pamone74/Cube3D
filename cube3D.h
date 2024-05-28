#ifndef CUBE3D_H
#define CUBE3D_H
#define HEIGHT 700
#define WIDTH 550
#include  <stdlib.h>
#include <mlx.h>
#include <math.h>
// Map information
#define WALL 1
#define EMPTY 0
#define NORTH N
#define SOUTH S
#define EAST E 
#define WEST W 

// tile
#define TILE_SIZE 50

// Players settings
#define PLAYER_ANGLE 0  // Now Let's say when the game starts, the player angle should be 0;
#define PLAYER_SPEED 1  // we could have used 0.005 * time delta, unfortunately we cannot use time.h here
#define PLAYER_ROT_SPEED 0.05
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

typedef struct s_colling
{
    double x;
    double y;
}t_collidng;

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
    double  player_angle;
    t_data image;
    t_map_data *map_data;
    char **colliding;

}t_window;

typedef struct s_player{
    int     player_pos_x;
    int     player_pos_y;
    char    player_view;
    int     player_angle;
    double  player_speed;
    double  player_rot;
    int     player_size;

}t_player;


// utils.c
t_map_data* ft_extract_map(char **argv, int ac);
int ft_player_pos(char **map, t_player *player);
int validate_map(char **map);
int ft_validate_map(char **map);
char **ft_try_split(char **argv);



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


// wall collision
int ft_collision(t_window *mlx);
#endif