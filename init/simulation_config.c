#include "../cub3d.h"

static void	init_screen_dimensions(t_dimensions_config *dimensions_config)
{
	dimensions_config->screen_width = 1920;
	dimensions_config->screen_height = 1080;
}

static void	init_textures_dimensions(t_dimensions_config *dimensions_config)
{
	dimensions_config->texture_width = 256;
	dimensions_config->texture_height = 256;
}

static void	init_player_move_speed(t_player_speed_config *player_speed_config)
{
	player_speed_config->linear = 0.04;
	player_speed_config->lateral = 0.04;
}

static void	init_camera_rotation_speed(t_camera_config *camera_config)
{
	camera_config->rotation_speed = 0.025;
}

void	init_simulation_parameters(t_resources *resources)
{
	init_screen_dimensions(&(resources->dimensions_config));
	init_textures_dimensions(&(resources->dimensions_config));
	init_player_move_speed(&(resources->player_speed_config));
	init_camera_rotation_speed(&(resources->camera_config));
}
