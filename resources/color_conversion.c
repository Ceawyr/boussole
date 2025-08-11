#include "../cub3d.h"

static uint32_t	convert_rgb_to_rgba(int rgb[3])
{
	uint32_t	alpha;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	final_color;

	alpha = 0xFF;
	red = (uint32_t)rgb[0];
	green = (uint32_t)rgb[1];
	blue = (uint32_t)rgb[2];
	red = red << 24;
	green = green << 16;
	blue = blue << 8;
	final_color = (red | green | blue | alpha);
	return (final_color);
}

void	set_floor_and_ceiling_colors(t_resources *resources)
{
	resources->floor_argb = convert_rgb_to_rgba(resources->map_data.floor_color);
	resources->ceiling_argb = convert_rgb_to_rgba(resources->map_data.ceiling_color);
}
