/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:48:58 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/11 22:50:29 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_pixel_safe(mlx_image_t *img, int x, int y)
{
	int			index;
	uint8_t		*pixel;

	if (x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
		return (0x00000000);
	index = (y * img->width + x) * 4;
	pixel = &img->pixels[index];
	return (((uint32_t)pixel[3] << 24)
		| ((uint32_t)pixel[0] << 16)
		| ((uint32_t)pixel[1] << 8)
		| ((uint32_t)pixel[2]));
}

double	calculate_player_angle(const t_player_data *player)
{
	return (atan2(player->direction_x, -player->direction_y));
}
