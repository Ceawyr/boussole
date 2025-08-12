/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:48:58 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/12 20:18:55 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_pixel_safe(mlx_image_t *img, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
		return (0x00000000);
	return (convert_rgba_to_argb(img, x, y));
}

double	calculate_player_angle(const t_player_data *player)
{
	return (atan2(player->direction_x, -player->direction_y));
}
