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