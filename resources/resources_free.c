#include "../cub3d.h"

static void	free_image(t_resources *resources, mlx_image_t **image)
{
	if (*image != NULL)
	{
		mlx_delete_image(resources->mlx, *image);
		*image = NULL;
	}
}

static void	list_images_to_free(t_resources *resources)
{
	free_image(resources, &(resources->north_image));
	free_image(resources, &(resources->south_image));
	free_image(resources, &(resources->west_image));
	free_image(resources, &(resources->east_image));
	free_image(resources, &(resources->screen));
}

static void	free_mlx(t_resources *resources)
{
	if (resources->mlx != NULL)
	{
		mlx_terminate(resources->mlx);
		resources->mlx = NULL;
	}
}

void	free_game_resources(t_resources	*resources)
{
	if (resources->mlx == NULL)
		return ;
	list_images_to_free(resources);
	free_compass_resources(resources);
	free_mlx(resources);
}
