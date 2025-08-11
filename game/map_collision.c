#include "../cub3d.h"




static inline int has_map_wall_at(t_map_data *map_data, int y, int x)
{
    if (y < 0 || y >= map_data->map_height
        || x < 0 || x >= map_data->map_width)
    {
        return (1);
    }
    if (map_data->map[y][x] == '1')
    {
        return (1);
    }
    return (0);
}



void attempt_player_move(t_player_data *player_data, t_map_data *map_data, double delta_x, double delta_y)
{
    double new_position_x;
    double new_position_y;

    int new_position_x_truncate;
    int new_position_y_truncate;


    new_position_x = player_data->position_x + delta_x;
    new_position_y = player_data->position_y + delta_y;


    new_position_x_truncate  = (int)new_position_x;
    new_position_y_truncate  = (int)new_position_y;


    if (has_map_wall_at(map_data, new_position_y_truncate, new_position_x_truncate) == 1)
        return ;

    if (has_map_wall_at(map_data, (int)player_data->position_y, new_position_x_truncate) == 0)
        player_data->position_x = new_position_x;

    if (has_map_wall_at(map_data, new_position_y_truncate, (int)player_data->position_x) == 0)
        player_data->position_y = new_position_y;
}


