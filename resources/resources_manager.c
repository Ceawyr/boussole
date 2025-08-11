#include "../cub3d.h"

void	init_game_data(t_resources	*resources)
{
	set_player_orientation(resources);
	set_floor_and_ceiling_colors(resources);
	resources->mlx = mlx_init(resources->dimensions_config.screen_width,
			resources->dimensions_config.screen_height, "cub3D", false);
	if (resources->mlx == NULL)
	{
		write_and_exit_error(ERROR_MLX_INIT, &(resources->map_data));
	}
	// mlx_set_cursor_mode(resources->mlx, MLX_MOUSE_DISABLED);
	resources->north_image = load_image_texture(resources,
			resources->map_data.north_texture_path);
	resources->south_image = load_image_texture(resources,
			resources->map_data.south_texture_path);
	resources->west_image = load_image_texture(resources,
			resources->map_data.west_texture_path);
	resources->east_image = load_image_texture(resources,
			resources->map_data.east_texture_path);
	init_compass(resources);
}
