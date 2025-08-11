#include "../cub3d.h"



void    init_screen(t_resources *resources)
{

    resources->screen = mlx_new_image(resources->mlx,
									resources->dimensions_config.screen_width,
									resources->dimensions_config.screen_height);
    if (resources->screen == NULL)
    {
		write_and_exit_with_graphics_error(ERROR_NEW_IMAGE, resources);
	}
    if (mlx_image_to_window(resources->mlx, resources->screen, 0, 0) < 0)
	{
		write_and_exit_with_graphics_error(ERROR_DISPLAY_IMAGE, resources);
	}
}


