#include "../cub3d.h"

static void	set_direction_and_plane_north_south(t_resources	*resources)
{
	if (resources->map_data.player_direction == 'N')
	{
		resources->player_data.direction_x = 0;
		resources->player_data.direction_y = -1;
		resources->player_data.plane_x = 0.66;
		resources->player_data.plane_y = 0;
	}
	else if (resources->map_data.player_direction == 'S')
	{
		resources->player_data.direction_x = 0;
		resources->player_data.direction_y = 1;
		resources->player_data.plane_x = -0.66;
		resources->player_data.plane_y = 0;
	}
}

static void	set_direction_and_plane_west_east(t_resources	*resources)
{
	if (resources->map_data.player_direction == 'E')
	{
		resources->player_data.direction_x = 1;
		resources->player_data.direction_y = 0;
		resources->player_data.plane_x = 0;
		resources->player_data.plane_y = 0.66;
	}
	else if (resources->map_data.player_direction == 'W')
	{
		resources->player_data.direction_x = -1;
		resources->player_data.direction_y = 0;
		resources->player_data.plane_x = 0;
		resources->player_data.plane_y = -0.66;
	}
}

void	set_player_orientation(t_resources	*resources)
{
	resources->player_data.position_x = resources->map_data.player_x_start;
	resources->player_data.position_y = resources->map_data.player_y_start;
	set_direction_and_plane_north_south(resources);
	set_direction_and_plane_west_east(resources);
}
