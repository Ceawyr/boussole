/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:44:08 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/12 18:40:23 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_compass(t_resources *resources)
{
	resources->compass_background = load_image_texture(resources,
			"./images/compass_bg.png");
	resources->compass_needle = load_image_texture(resources,
			"./images/compass_needle.png");
	if (!resources->compass_background || !resources->compass_needle)
		write(2, "Warning: Could not load compass images\n", 40);
}

void	free_compass_resources(t_resources *resources)
{
	if (resources->compass_background)
	{
		mlx_delete_image(resources->mlx, resources->compass_background);
		resources->compass_background = NULL;
	}
	if (resources->compass_needle)
	{
		mlx_delete_image(resources->mlx, resources->compass_needle);
		resources->compass_needle = NULL;
	}
}
