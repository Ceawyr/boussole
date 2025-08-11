/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:47:42 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/11 22:48:41 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_needle_data(t_needle_data *data, mlx_image_t *needle,
							double angle)
{
	data->cos_angle = cos(-angle);
	data->sin_angle = sin(-angle);
	data->half_width = needle->width / 2;
	data->half_height = needle->height / 2;
}

static void	draw_needle_pixel(mlx_image_t *screen, mlx_image_t *needle,
							t_compass_pos *pos, t_needle_data *data)
{
	int			dy;
	int			dx;
	int			src_x;
	int			src_y;
	uint32_t	color;

	dy = -50;
	while (dy <= 50)
	{
		dx = -50;
		while (dx <= 50)
		{
			src_x = (int)(dx * data->cos_angle - dy * data->sin_angle)
				+ data->half_width;
			src_y = (int)(dx * data->sin_angle + dy * data->cos_angle)
				+ data->half_height;
			if (src_x >= 0 && src_x < (int)needle->width
				&& src_y >= 0 && src_y < (int)needle->height)
			{
				color = get_pixel_safe(needle, src_x, src_y);
				if ((color >> 24) > 0)
					safe_put_pixel(screen, pos->center_x + dx,
						pos->center_y + dy, color);
			}
			dx++;
		}
		dy++;
	}
}

static void	draw_compass_background(t_resources *resources,
									t_compass_pos *pos)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	color;

	y = 0;
	while (y < resources->compass_background->height)
	{
		x = 0;
		while (x < resources->compass_background->width)
		{
			color = get_pixel_safe(resources->compass_background, x, y);
			if ((color >> 24) > 0)
				safe_put_pixel(resources->screen, pos->compass_x + x,
					pos->compass_y + y, color);
			x++;
		}
		y++;
	}
}

static void	init_compass_position(t_resources *resources, t_compass_pos *pos)
{
	pos->compass_x = (resources->dimensions_config.screen_width
			- resources->compass_background->width) / 2;
	pos->compass_y = resources->dimensions_config.screen_height
		- resources->compass_background->height - 20;
	pos->center_x = pos->compass_x
		+ resources->compass_background->width / 2;
	pos->center_y = pos->compass_y
		+ resources->compass_background->height / 2;
}

void	render_compass(t_resources *resources)
{
	t_compass_pos	pos;
	t_needle_data	needle_data;
	double			player_angle;

	if (!resources->compass_background || !resources->compass_needle)
		return ;
	init_compass_position(resources, &pos);
	draw_compass_background(resources, &pos);
	player_angle = calculate_player_angle(&resources->player_data);
	init_needle_data(&needle_data, resources->compass_needle, player_angle);
	draw_needle_pixel(resources->screen, resources->compass_needle,
		&pos, &needle_data);
}
