#include "../cub3d.h"

static void	init_empty_resources(t_resources *resources)
{
	resources->mlx = NULL;
	resources->north_image = NULL;
	resources->south_image = NULL;
	resources->west_image = NULL;
	resources->east_image = NULL;
	resources->screen = NULL;
	resources->floor_argb = 0;
	resources->ceiling_argb = 0;
}

static void	init_empty_map_data(t_map_data *map_data)
{
	map_data->map = NULL;
	map_data->map_width = 0;
	map_data->map_height = 0;

	// rouge
	map_data->floor_color[0] = 0;
	// vert
    map_data->floor_color[1] = 0;
	// bleu
    map_data->floor_color[2] = 0;
	map_data->is_floor_already_defined = 0;

	// rouge
	map_data->ceiling_color[0] = 0;
	// vert
    map_data->ceiling_color[1] = 0;
	// bleu
    map_data->ceiling_color[2] = 0;
	map_data->is_ceiling_already_defined = 0;

	map_data->north_texture_path = NULL;
	map_data->south_texture_path = NULL;
	map_data->west_texture_path = NULL;
	map_data->east_texture_path = NULL;

	map_data->player_direction = '\0';
	map_data->player_x_start = 0;
	map_data->player_y_start = 0;
}

static void	init_empty_player_data(t_player_data *player_data)
{
	player_data->position_x = 0;
	player_data->position_y = 0;
	player_data->direction_x = 0;
	player_data->direction_y = 0;
	player_data->plane_x = 0;
	player_data->plane_y = 0;
}

static void	init_empty_config(t_player_speed_config *player_speed_config,
	t_camera_config *camera_config, t_dimensions_config *dimensions_config)
{
	player_speed_config->linear = 0;
	player_speed_config->lateral = 0;
	camera_config->rotation_speed = 0;
	dimensions_config->screen_width = 0;
	dimensions_config->screen_height = 0;
	dimensions_config->texture_width = 0;
	dimensions_config->texture_height = 0;
}

void	sanitize_structs(t_resources *resources)
{
	init_empty_resources(resources);
	init_empty_map_data(&(resources->map_data));
	init_empty_player_data(&(resources->player_data));
	init_empty_config(&(resources->player_speed_config),
		&(resources->camera_config), &(resources->dimensions_config));
}
