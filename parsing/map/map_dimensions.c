/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:12:05 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:12:05 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	has_map_started(char **line, int fd, t_map_data *map_data, int i)
{
	int	len;

	if ((*line)[i] != '1')
	{
		free(*line);
		*line = get_next_line(fd, 0);
		return (0);
	}
	map_data->map_height = map_data->map_height + 1;
	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
		len--;
	if (map_data->map_width < len)
		map_data->map_width = len;
	return (1);
}

static int	get_height_and_width(char **line, int fd,
									t_map_data *map_data, int i)
{
	int	len;

	if ((*line)[i] != '1')
	{
		free(*line);
		*line = get_next_line(fd, 0);
		return (2);
	}
	map_data->map_height = map_data->map_height + 1;
	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
		len--;
	if (map_data->map_width < len)
		map_data->map_width = len;
	return (1);
}

static void	has_map_multiple_blocks(int map_status, char **line,
										int fd, t_map_data *map_data)
{
	int	i;

	if (*line == NULL)
		return ;
	i = skip_white_space(*line);
	if (map_status == 2)
	{
		if ((*line)[i] == '1')
		{
			free(*line);
			clear_remaining_lines_gnl(fd);
			write_close_and_exit(fd, ERROR_MAP_NOT_SINGLE_BLOCK, map_data);
		}
		else if ((*line)[i] != '\0')
		{
			free(*line);
			clear_remaining_lines_gnl(fd);
			write_close_and_exit(fd, ERROR_MAP_NOT_AT_THE_END, map_data);
		}
	}
	free(*line);
	*line = get_next_line(fd, 0);
}

void	get_map_dimensions(int fd, t_map_data *map_data)
{
	char	*line;
	int		map_status;
	int		i;

	map_status = 0;
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		i = skip_white_space(line);
		if (map_status == 0)
		{
			map_status = has_map_started(&line, fd, map_data, i);
			if (map_status == 0)
				continue ;
		}
		else if (map_status == 1)
			map_status = get_height_and_width(&line, fd, map_data, i);
		has_map_multiple_blocks(map_status, &line, fd, map_data);
	}
}
