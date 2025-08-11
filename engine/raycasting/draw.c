#include "../../cub3d.h"






static void draw_ceiling_pixel_column(t_resources *resources, int screen_x, int wall_start_y)
{
    int screen_y;

    screen_y = 0;
    while (screen_y < wall_start_y)
    {
        safe_put_pixel(resources->screen, screen_x, screen_y, resources->ceiling_argb);
        screen_y++;
    }
}


static void draw_floor_pixel_column(t_resources *resources, int screen_x, int screen_y)
{
    while (screen_y < resources->dimensions_config.screen_height)
    {
        safe_put_pixel(resources->screen, screen_x, screen_y, resources->floor_argb);
        screen_y++;
    }
}

static int	ensure_texture_y_is_valid(double current_texture_y, int texture_height)
{
	int valid_texture_y;

	valid_texture_y = (int)current_texture_y % texture_height;

	if (valid_texture_y < 0)
    {
		valid_texture_y += texture_height;
    }
	return (valid_texture_y);
}



static void draw_wall_pixel_column(t_resources *resources, int screen_x, const t_raycast_data *ray, t_ray_column_norm_helper *helper)
{
    int         screen_y;
    double      texture_advance_per_screen_pixel;
    double      current_texture_y;
    uint32_t    texture_color;
    uint32_t    final_color;

    screen_y = helper->wall_start_y;
    texture_advance_per_screen_pixel = (double)helper->texture->height / helper->wall_height_in_pixels;
    current_texture_y = (helper->wall_start_y - ((resources->dimensions_config.screen_height - helper->wall_height_in_pixels) / 2)) * texture_advance_per_screen_pixel;
    
    while (screen_y <= helper->wall_end_y)
    {
        texture_color = convert_rgba_to_argb(helper->texture, helper->wall_hit_x, ensure_texture_y_is_valid(current_texture_y, (int)helper->texture->height));
        if (ray->hit_side == 1)
            final_color = shade_color(texture_color);
        else
            final_color = texture_color;
        safe_put_pixel(resources->screen, screen_x, screen_y, final_color);
        current_texture_y += texture_advance_per_screen_pixel;
        screen_y++;
    }
}



void draw_entire_pixel_column(t_resources *resources, int screen_x, const t_raycast_data *ray, t_ray_column_norm_helper *helper)
{

    helper->wall_height_in_pixels = (int)(resources->dimensions_config.screen_height / ray->perp_distance);

    if (helper->wall_height_in_pixels <= 0)
        helper->wall_height_in_pixels = 1;

    helper->wall_start_y = (-helper->wall_height_in_pixels / 2) + resources->dimensions_config.screen_height / 2;
    helper->wall_end_y = ( helper->wall_height_in_pixels / 2) + resources->dimensions_config.screen_height / 2;

    if (helper->wall_start_y < 0) 
        helper->wall_start_y = 0;

    if (helper->wall_end_y >= resources->dimensions_config.screen_height) 
        helper->wall_end_y = resources->dimensions_config.screen_height - 1;


    draw_ceiling_pixel_column(resources, screen_x, helper->wall_start_y);

    draw_wall_pixel_column(resources, screen_x, ray, helper);
    
    draw_floor_pixel_column(resources, screen_x, helper->wall_end_y + 1);

}