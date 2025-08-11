#include "../cub3d.h"



void move_player_rotation(t_player_data *player_data, double angle)
{
    double old_direction_x;
    double old_plane_x;
    double cos_angle;
    double sin_angle;

    old_direction_x = player_data->direction_x;
    old_plane_x = player_data->plane_x;
    cos_angle = cos(angle);
    sin_angle = sin(angle);


    player_data->direction_x = player_data->direction_x * cos_angle - player_data->direction_y * sin_angle;
    player_data->direction_y = old_direction_x * sin_angle + player_data->direction_y * cos_angle;


    player_data->plane_x = player_data->plane_x * cos_angle - player_data->plane_y * sin_angle;
    player_data->plane_y = old_plane_x * sin_angle + player_data->plane_y * cos_angle;
}


void move_player_linear(t_player_data *player_data, t_map_data *map_data, double linear_speed, int direction)
{
    double delta_x;
    double delta_y;

    delta_x = direction * player_data->direction_x * linear_speed;
    delta_y = direction * player_data->direction_y * linear_speed;


    attempt_player_move(player_data, map_data, delta_x, delta_y);
}



void move_player_lateral(t_player_data *player_data, t_map_data *map_data, double lateral_speed, int direction)
{
    double delta_x;
    double delta_y;

    delta_x = direction * player_data->plane_x * lateral_speed;
    delta_y = direction * player_data->plane_y * lateral_speed;

    attempt_player_move(player_data, map_data, delta_x, delta_y);
}
