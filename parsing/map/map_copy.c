/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:11:19 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:11:19 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	set_sentinel_null(t_map_data *map_data)
{
	int	i;

	i = 0;
	while (i <= map_data->map_height)
	{
		map_data->map[i] = NULL;
		i++;
	}
}

static void	delete_newline_if_present(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

static int	has_map_started_to_copy(char **line, int fd)
{
	int	j;

	j = skip_white_space(*line);
	if ((*line)[j] != '1')
	{
		free(*line);
		*line = get_next_line(fd, 0);
		return (0);
	}
	return (1);
}

static void	fill_in_the_line(char *line, int fd, t_map_data *map_data, int i)
{
	map_data->map[i] = malloc_filled_with_space(map_data->map_width + 1, sizeof(char));
	if (map_data->map[i] == NULL)
	{
		free(line);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	ft_memcpy(map_data->map[i], line, ft_strlen(line));
	free(line);
}

void	copy_map(int fd, t_map_data *map_data)
{
	char	*line;
	int		map_status;
	int		i;

	i = 0;
	map_data->map = malloc(sizeof(char *) * (map_data->map_height + 1));
	if (map_data->map == NULL)
	{
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	set_sentinel_null(map_data);
	line = get_next_line(fd, 0);
	while (line != NULL && i < map_data->map_height)
	{
		map_status = has_map_started_to_copy(&line, fd);
		if (map_status == 0)
			continue ;
		delete_newline_if_present(line);
		fill_in_the_line(line, fd, map_data, i);
		i++;
		line = get_next_line(fd, 0);
	}
	free_residual_line_and_gnl(fd, &line);
	// map_data->map[i] = NULL;
}
