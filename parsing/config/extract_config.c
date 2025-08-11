/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:13:07 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:13:07 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	extract_config_from_line(char *line, t_map_data *map_data,
										int fd, char	*line_origin)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		get_north_texture_path(line + 2, map_data, fd, line_origin);
	if (ft_strncmp(line, "SO", 2) == 0)
		get_south_texture_path(line + 2, map_data, fd, line_origin);
	if (ft_strncmp(line, "WE", 2) == 0)
		get_west_texture_path(line + 2, map_data, fd, line_origin);
	if (ft_strncmp(line, "EA", 2) == 0)
		get_east_texture_path(line + 2, map_data, fd, line_origin);
	if (line[0] == 'F')
		get_floor_color(line + 1, map_data, fd, line_origin);
	if (line[0] == 'C')
		get_ceiling_color(line + 1, map_data, fd, line_origin);
}

static int	is_valid_identifier(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'F' || c == 'C' || c == '1')
		return (1);
	else
		return (0);
}

void	get_map_config(int fd, t_map_data *map_data)
{
	char	*line;
	int		i;

	line = get_next_line(fd, 0);
	if (line == NULL)
		write_close_and_exit(fd, ERROR_EMPTY_FILE, map_data);
	while (line != NULL)
	{
		i = skip_white_space(line);
		if (line[i] == '\0')
		{
			free(line);
			line = get_next_line(fd, 0);
			continue ;
		}
		if (is_valid_identifier(line[i]) == 0)
		{
			free(line);
			clear_remaining_lines_gnl(fd);
			write_close_and_exit(fd, ERROR_UNKNOWN_IDENTIFIER, map_data);
		}
		extract_config_from_line(line + i, map_data, fd, line);
		free(line);
		line = get_next_line(fd, 0);
	}
}
