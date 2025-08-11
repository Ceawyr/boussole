/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:14:36 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:14:36 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	replace_carriage_ret_and_withspace_for_windows(t_map_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_data->map[i] != NULL && i < map_data->map_height)
	{
		j = 0;
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] == '\t' || map_data->map[i][j] == '\r')
			{
				map_data->map[i][j] = ' ';
			}
			j++;
		}
		i++;
	}
}

void	init_map_data(char *map, t_map_data *map_data)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		write_and_exit_error(ERROR_OPEN, map_data);
	get_map_config(fd, map_data);
	close(fd);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		write_and_exit_error(ERROR_OPEN, map_data);
	get_map_dimensions(fd, map_data);
	close(fd);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		write_and_exit_error(ERROR_OPEN, map_data);
	copy_map(fd, map_data);
	close(fd);
	replace_carriage_ret_and_withspace_for_windows(map_data);
	if (map_data->map == NULL || map_data->map_height == 0)
		write_and_exit_error(ERROR_EMPTY_MAP, map_data);
	ensure_config_ready(map_data);
	check_map_validity(map_data);
}
