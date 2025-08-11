/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:12:21 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:12:21 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	check_map_elements(t_map_data *map_data)
{
	int	i;
	int	j;
	int	nb_player;

	i = 0;
	j = 0;
	nb_player = 0;
	while (map_data->map[i] != NULL)
	{
		j = 0;
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] == 'N' || map_data->map[i][j] == 'S'
				|| map_data->map[i][j] == 'E' || map_data->map[i][j] == 'W')
				nb_player++;
			else if (map_data->map[i][j] != '1' && map_data->map[i][j] != '0'
				&& map_data->map[i][j] != 'N' && map_data->map[i][j] != 'S'
				&& map_data->map[i][j] != 'E' && map_data->map[i][j] != 'W'
				&& map_data->map[i][j] != ' ')
				write_and_exit_error(ERROR_INVALID_CHAR, map_data);
			j++;
		}
		i++;
	}
	return (nb_player);
}

static void	find_character_position(t_map_data *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->map_height)
	{
		x = 0;
		while (x < map_data->map_width)
		{
			if (map_data->map[y][x] == 'N' || map_data->map[y][x] == 'S'
				|| map_data->map[y][x] == 'E' || map_data->map[y][x] == 'W')
			{
				map_data->player_direction = map_data->map[y][x];
				map_data->player_x_start = x + 0.5;
				map_data->player_y_start = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	check_map_min_size_validity(t_map_data *map_data)
{
	if (!((map_data->map_width >= 4 && map_data->map_height >= 4)
			|| (map_data->map_width >= 3 && map_data->map_height >= 5)
			|| (map_data->map_width >= 5 && map_data->map_height >= 3)))
	{
		write_and_exit_error(ERROR_MAP_TOO_SMALL, map_data);
	}
}

void	check_map_validity(t_map_data *map_data)
{
	char	**map_copy;

	if (check_map_elements(map_data) != 1)
		write_and_exit_error(ERROR_NUMBER_CHARACTER, map_data);
	find_character_position(map_data);
	check_map_min_size_validity(map_data);
	map_copy = duplicate_map(map_data);
	flood_fill(map_copy, map_data->player_x_start, map_data->player_y_start, map_data);
	free_map_copy(map_copy);
}
