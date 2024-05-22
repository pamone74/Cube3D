#include "/home/pamone/Desktop/mlx/cube3D.h"
#include "/home/pamone/Desktop/mlx/get_next_line/get_next_line.h"
// #include "/home/pamone/Desktop/mlx/libft/libft.h"
#include <unistd.h>

int main(void)
{
    t_map_data *data;

    t_map_data * mem = malloc(sizeof(t_map_data));
    if(!mem)
        return 0;

    int fd = open("/home/pamone/Desktop/mlx/map1.cub", O_RDONLY);
    if (fd == -1)
        return (0);
    char *line;
    line = 0;
    int i = 0;
    mem->map = malloc(sizeof(char*) * 100);
            if(!mem->map)
                return 0;
    while(1)
    {
        line = get_next_line(fd);
        if(line && strncmp(line, "NO", 2) == 0)
            mem->NO = strdup(line);
        if(line && strncmp(line, "SO", 2) == 0)
            mem->SO = strdup(line);
        if(line && strncmp(line, "F", 1) == 0)
            mem->color_floor = atoi(strdup(line+2));
        // printf("%i\n", line[0]);
        if(line && line[0] == 49)  
            mem->map[i++] = strdup(line);

        free(line);
        if(!line)
            break;
    }
    close(fd);
    i = 0;

    while(mem->map[i])
    {
        int j = 0;
        while(mem->map[i][j])
        {
            if(mem->map[i][j] == 'E')
                printf("(%d , %d)\n", i, j);
            j++;
        }
        i++;
    }
    

}