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


// utils.c
char ** ft_extract_map(char **argv, int ac);
int ft_player_pos(char **map, t_player *player);
int validate_map(char **map);
int ft_validate_map(char **map);

#endif