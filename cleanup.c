#include "cub3d.h"

static void free_textures_map_data(t_map_data *map_data)
{
    if (map_data->north_texture_path != NULL)
    {
	    free(map_data->north_texture_path);
	    map_data->north_texture_path = NULL;
    }
    if (map_data->south_texture_path != NULL)
    {
	    free(map_data->south_texture_path);
	    map_data->south_texture_path = NULL;
    }
    if (map_data->west_texture_path != NULL)
    {
	    free(map_data->west_texture_path);
	    map_data->west_texture_path = NULL;
    }
    if (map_data->east_texture_path != NULL)
    {
	    free(map_data->east_texture_path);
	    map_data->east_texture_path = NULL;
    }
}

void	free_map_data(t_map_data *map_data)
{
	int	i;

    if (map_data == NULL)
        return ;
    if (map_data->map != NULL)
    {
        i = 0;
        while (map_data->map[i] != NULL)
            free(map_data->map[i++]);
        free(map_data->map);
        map_data->map = NULL;
    }
    free_textures_map_data(map_data);
}

void	write_and_exit_error(const char *str, t_map_data *map_data)
{
	write(2, str, ft_strlen(str));
    free_map_data(map_data);
	exit(1);
}

void	write_and_exit_with_graphics_error(const char *str,
                                            t_resources *resources)
{
    write(2, str, ft_strlen(str));
    free_game_resources(resources);
    free_map_data(&(resources->map_data));
	exit(1);
}
