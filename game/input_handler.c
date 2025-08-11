#include "../cub3d.h"




static void handle_player_movement(mlx_t *mlx,
                                t_map_data *map_data,
                                t_resources *resources,
                                t_player_data *player_data)
{
    double  linear_speed;
    double  lateral_speed;
    double  rotation_speed;

    linear_speed = resources->player_speed_config.linear;
    lateral_speed = resources->player_speed_config.lateral;
    rotation_speed = resources->camera_config.rotation_speed;

    if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
        linear_speed *= 1.5;

    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        move_player_rotation(player_data, -rotation_speed);
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        move_player_rotation(player_data, rotation_speed);

    if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
        move_player_linear(player_data, map_data, linear_speed, +1);
    if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
        move_player_linear(player_data, map_data, linear_speed, -1);

    if (mlx_is_key_down(mlx, MLX_KEY_A))
        move_player_lateral(player_data, map_data, lateral_speed, -1);
    if (mlx_is_key_down(mlx, MLX_KEY_D))
        move_player_lateral(player_data, map_data, lateral_speed, +1);
}





void	handle_keypress_input(t_resources *resources)
{
    mlx_t			*mlx;
    t_map_data		*map_data;
	t_player_data	*player_data;

	if (mlx_is_key_down(resources->mlx, MLX_KEY_ESCAPE))
    {
        write(1, INFO_ESCAPE_EXIT, ft_strlen(INFO_ESCAPE_EXIT));
        free_game_resources(resources);
        free_map_data(&(resources->map_data));
	    exit(0);
    }
	
    mlx = resources->mlx;
	map_data = &resources->map_data;
    player_data = &resources->player_data;

    handle_player_movement(mlx, map_data, resources, player_data);
}


