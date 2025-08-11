#include "../../cub3d.h"






static void setup_raycast_traversal(const t_resources *resources, t_raycast_data *ray)
{
    if (ray->ray_direction_x < 0)
    {
        ray->advance_direction_x = -1;
        ray->dist_to_next_x = (resources->player_data.position_x - ray->ray_current_tile_x) * ray->dist_per_tile_x;
    }
    else
    {
        ray->advance_direction_x = 1;
        ray->dist_to_next_x = (ray->ray_current_tile_x + 1.0 - resources->player_data.position_x) * ray->dist_per_tile_x;
    }
    if (ray->ray_direction_y < 0)
    {
        ray->advance_direction_y = -1;
        ray->dist_to_next_y = (resources->player_data.position_y - ray->ray_current_tile_y) * ray->dist_per_tile_y;
    }
    else
    {
        ray->advance_direction_y = 1;
        ray->dist_to_next_y = (ray->ray_current_tile_y + 1.0 - resources->player_data.position_y) * ray->dist_per_tile_y;
    }
}




void init_raycast(const t_resources *resources, int screen_x, t_raycast_data *ray)
{
    double ray_position_in_fov;

    ray_position_in_fov = 2.0 * screen_x / (double)resources->dimensions_config.screen_width - 1.0;

    ray->ray_direction_x = resources->player_data.direction_x + resources->player_data.plane_x * ray_position_in_fov;
    ray->ray_direction_y = resources->player_data.direction_y + resources->player_data.plane_y * ray_position_in_fov;

    ray->ray_current_tile_x = (int)resources->player_data.position_x;
    ray->ray_current_tile_y = (int)resources->player_data.position_y;

    // if (ray->ray_direction_x == 0)
    //     ray->dist_per_tile_x = 1e30;
    // else
    //     ray->dist_per_tile_x = fabs(1.0 / ray->ray_direction_x);

    // if (ray->ray_direction_y == 0)
    //     ray->dist_per_tile_y = 1e30;
    // else
    //     ray->dist_per_tile_y = fabs(1.0 / ray->ray_direction_y);




    if (fabs(ray->ray_direction_x) < 1e-10)
        ray->dist_per_tile_x = INFINITY;
    else
        ray->dist_per_tile_x = 1.0 / fabs(ray->ray_direction_x);

    if (fabs(ray->ray_direction_y) < 1e-10)
        ray->dist_per_tile_y = INFINITY;
    else
        ray->dist_per_tile_y = 1.0 / fabs(ray->ray_direction_y);



    setup_raycast_traversal(resources, ray);

}

