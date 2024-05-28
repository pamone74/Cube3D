#include "/home/pamone/Desktop/mlx/cube3D.h"
#include "/home/pamone/Desktop/mlx/get_next_line/get_next_line.h"
#include "/home/pamone/Desktop/mlx/libft/libft.h"
#include <unistd.h>

char **ft_try_split(char **argv)
{
    // t_map_data *memory;
    // memory->map = malloc(sizeof(char *) * 100);
    // if (!memory->map)
    //     return 0;
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        return 0;
    char *line =0;
    char **splted = malloc(sizeof(char *) * 100);
    if(!splted)
        return 0;
    int i = 0;
    while(i < 4)
    {
        line = get_next_line(fd);
        splted = ft_split(ft_strdup(line), '\n');
        free(line);
        i++;
    }
    return splted;
}
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

int ft_validate_texture(int current, int next)
{
    // I wil return different result for different textures:
    // NO(1), EA(2), WE(3), SO(4) and 0 for nor found
    if(current == 'N' && next == 'O') // NO
        return (1);
    else if(current == 'S' && next == 'O') // SO
        return (2);
    else if(current == 'W' && next == 'E') // WE
        return (3);
    else if(current =='E' && next == 'E')// EA
        return (4);
    else
        return 0;
}
// Under develoment
char **map(char** map)
{

    // check for the leading spaces, the valid map should have path for the textures, colors, and map datas
    // spaces are allowed and we need to parse that as well
    // map can as well have spaces in between and that's fine, we can treat it as part of wall or ignore it, 
    //      so in this case i will just ignore it.
    int i = 0;
    int j = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            // skip the leading spaces
            if (map[i][j] == ' ')
                j++;
            //  we need to check for the wall textures path
            //  we have four textures to take care of: NO, EA, WE,SO, leading char.
            if (ft_validate_texture(map[i][j], map[i][j + 1]) == 1) // NO
            {
                // We need to exepect spaces eg NO        /path/texture.xmp
                // thera are two things we can do here, store it and strim the spaces later or we strim here directly
            }
        }
        i++;
    }
    return NULL;
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel/8));
    *(unsigned int *)dst = color;
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
    mlx->colliding = malloc(sizeof(char *) * 100);
    if(!mlx->colliding)
    {
        printf("Issues with calling malloc\n");
        return;
    }
    mlx->colliding = NULL;
    while(x < row)
    {
        y = 0;
        while(y < (int)strlen(tilemap[x])) 
        {
            if(tilemap[x][y] == '1')
            {
                
                draw_rect(mlx, y * TILE_SIZE, x*TILE_SIZE, TILE_SIZE, 0x0000FF00);  
                // mlx->colliding[x][y] = '1';
                // printf("I am here  and mlx->colliding %d\n", mlx->colliding[x][y] );
            }
        
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
    printf("Is player colliding ?  %d \n",ft_collision(mlx) );
    int flag = 0;
    if (ft_collision(mlx) && !flag){

        mlx->player_pos_x -= dx;
        mlx->player_pos_y -= dy;
        flag = 1;
    }else

    {
        flag = 0;
        mlx->player_pos_x += dx;
        mlx->player_pos_y += dy;
    }
    
    // left key
    if (keyssys == 65361)
        mlx->player_angle -= PLAYER_ROT_SPEED;
    // Right Key
    if (keyssys == 65363)
        mlx->player_angle += PLAYER_ROT_SPEED;
    mlx->player_angle = fmod(mlx->player_angle, 2 * PI);
    printf("%f", mlx->player_angle);
    if (mlx->player_angle < 0)
        mlx->player_angle += 2 * PI; // Ensure angle is positive
    // For every key we press the player's position needs to be update, i do not kmow if clearing the window is the best thing to do but i will update as i go along
    // printf("The key pressed is %c\n", keyssys);
    mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
    ft_render(mlx);
    return 0;

}



// =================== Render the window ========================

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




// ============================================== Init function ============================================

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


// =================================================== get current post ======================================================

int ft_check_wall(t_window *mlx)
{
    (void)mlx;
    // get the current tile where the player is

    // if (mlx->player_pos_x && mlx->player_pos_y )
    return 0;
}

//  ================================================== Check for collison with walls =========================================
int ft_collision(t_window *mlx)
{
    char **map = mlx->map_data->map;
    int player_tile_x = (int)(mlx->player_pos_x / TILE_SIZE); // Convert player position to tile coordinates
    int player_tile_y = (int)(mlx->player_pos_y / TILE_SIZE);

    // Check if player is out of bounds
    if (player_tile_x < 0 || player_tile_x >= WIDTH || player_tile_y < 0 || player_tile_y >= HEIGHT)
        return 1; // Collision with boundary walls

    // Check if the tile at the player's position is a wall
    if (map[player_tile_y][player_tile_x] == '1')
        return 1; // Collision with a wall

    return 0; // No collision
}
