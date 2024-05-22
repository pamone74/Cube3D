#include "/home/pamone/Desktop/mlx/cube3D.h"
#include "/home/pamone/Desktop/mlx/get_next_line/get_next_line.h"
#include <unistd.h>
char** ft_extract_map(char **argv, int ac)
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
        memory->map = malloc(sizeof(char *) * 100);
        if(!memory->map)
            return 0;
        while(1)
        {
            line = get_next_line(fd);
            if(line && strncmp(line, "NO", 2) == 0)
                memory->NO = strdup(line);
            if(line && strncmp(line, "SO", 2) == 0)
                memory->SO = strdup(line);
            if(line && strncmp(line, "F", 1) == 0)
                memory->color_floor = atoi(strdup(line+2));
            if(line && line[0] == 49)  
                memory->map[i++] = strdup(line);

            free(line);
            if(!line)
                break;
        }
        close(fd);
        return memory->map;
    }
    return 0;
}

int ft_get_char_in_map(char **map)
{
    int i;
    i = 0;
    while(map[i])
    {
        
        char * pointer = strpbrk(map[i], "NWES");
        if (pointer)
            return pointer[0];
        i++;

    }
    return 0;
}

int ft_player_pos(char **map, t_player *player)
{
    int i;
    int j;
    int flag;
    flag = 1;
    if(!map && !player)
        return 0;
    i =0;
    while (map[i])
    {
       j = 0;
       while(map[i][j])
       {
            if((map[i][j] == 'E' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W') && flag)
            {
                if (ft_get_char_in_map(map))
                    player->player_view = ft_get_char_in_map(map);
                else
                    return 0; // Here we return when we have not found the character sets in the map
                player->player_pos_x = i;
                player->player_pos_y = j;
                flag = 0;
                return 1;
            }
            j++;
       }
       i++;
    }
    return 0;
    
}

// validate the map
int validate_map(char **map)
{
    size_t i = 0;
    int j = 0;
    size_t count_holder;
    // count the size of map
    size_t count = 0;
    
    while(map[count])
        count++;
    count_holder = count;
    printf("%ld\n", count);
    // check top and bottom rows
    while(i < strlen(map[j]) && --count_holder)
    {
        if(map[0][i] != '1' || map[count-1][i] != '1')
        {
            printf("Invalid map Wall not closed \n");
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
        // printf("count == %ld ld == %ld\n", count, i);
        // printf("map[%ld][0] = %c map[%ld][%ld]) = %c\n", i, map[i][0] ,i,strlen(map[i])-2, map[i][strlen(map[i])-2] );
        if(map[i][0] != '1' || map[i][strlen(map[i])-2] != '1')
        {
            printf("Invalid map Wall not closed \n");
            // printf("Invalid map 2 map[%ld][0] = %c map[%ld][%ld]) = %c\n", i, map[i][0] ,i,strlen(map[i])-2, map[i][strlen(map[i])-2] );
            return 0;
        }
        //  for whatever reason, it was not checking the last corner
        if (i == count -1)
        {
            if(map[i][0] != '1' || map[i][strlen(map[i])-1] != '1')
        {
            printf("Invalid map Wall not closed \n");
            // printf("Invalid map 2 map[%ld][0] = %c map[%ld][%ld]) = %c\n", i, map[i][0] ,i,strlen(map[i])-2, map[i][strlen(map[i])-2] );
            return 0;
        }
        }
        i++;
    }
    return 1;
}
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
            if(map[i][j] != '1' || map[i][j] != '0')
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