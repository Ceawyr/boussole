/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:10:39 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:10:39 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**duplicate_map(t_map_data *map_data)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (map_data->map_height + 1));
	if (map_copy == NULL)
		write_and_exit_error(ERROR_ALLOC, map_data);
	while (i < map_data->map_height)
	{
		map_copy[i] = ft_strdup(map_data->map[i]);
		if (map_copy[i] == NULL)
		{
			free_map_copy(map_copy);
			write_and_exit_error(ERROR_ALLOC, map_data);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	flood_fill(char **map_copy, int x, int y, t_map_data *map_data)
{
	if (y < 0 || y >= map_data->map_height
		|| x < 0 || x >= map_data->map_width)
	{
		free_map_copy(map_copy);
		write_and_exit_error(ERROR_MAP_NOT_CLOSED, map_data);
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	if (map_copy[y][x] == ' ' || map_copy[y][x] == '\0')
	{
		free_map_copy(map_copy);
		write_and_exit_error(ERROR_MAP_NOT_CLOSED, map_data);
	}
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, map_data);
	flood_fill(map_copy, x - 1, y, map_data);
	flood_fill(map_copy, x, y + 1, map_data);
	flood_fill(map_copy, x, y - 1, map_data);
}
