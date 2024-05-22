#include "cube3D.h"
#include <stdio.h>
int main(int ac, char *argv[])
{
    if (ac == 2)
    {
        char *map = argv[1];
        if (map)
        {
            int i = 0;
            char **mapp = ft_extract_map(argv, ac);
            while(mapp[i])
                printf("%s", mapp[i++]);
            printf("\n");
            int validate = ft_validate_map(mapp);
            printf("%d", validate);
            t_player *player = malloc(sizeof(t_player));
            if (mapp)
            {
                int rt = ft_player_pos(mapp, player);
                if (rt)
                    printf("\nhere rt == %i (%i, %i) pos == %c\n", rt, player->player_pos_x, player->player_pos_y, player->player_view);
                else
                    printf("Error\n");
            }
        }
    }
}