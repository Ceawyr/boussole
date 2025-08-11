/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:13:01 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:13:01 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	validate_and_store_rgb(char **rgb_tab_sanitized,
	t_map_data *map_data, const char *type)
{
	int	i;
	int	value;
	int	is_valid;
	int	*target;

	if (ft_strncmp(type, "floor", 5) == 0)
		target = map_data->floor_color;
	else if (ft_strncmp(type, "ceiling", 7) == 0)
		target = map_data->ceiling_color;
	else
		return (-1);
	i = 0;
	while (i < 3)
	{
		value = ft_atoi_with_validation(rgb_tab_sanitized[i], &is_valid);
		if (is_valid == 0 || value < 0 || value > 255)
			return (-1);
		target[i] = value;
		i++;
	}
	return (0);
}

static int	parse_rgb_values(char *rgb_str_sanitized,
								t_map_data *map_data, const char *type)
{
	char	**rgb_tab_sanitized;
	int		i;

	rgb_tab_sanitized = ft_split(rgb_str_sanitized, ',');
	if (rgb_tab_sanitized == NULL)
		return (-1);
	i = 0;
	while (rgb_tab_sanitized[i] != NULL)
		i++;
	if (i != 3)
	{
		free_tab_rgb(rgb_tab_sanitized);
		return (-1);
	}
	if (validate_and_store_rgb(rgb_tab_sanitized, map_data, type) == -1)
	{
		free_tab_rgb(rgb_tab_sanitized);
		return (-1);
	}
	free_tab_rgb(rgb_tab_sanitized);
	return (0);
}

static void	validate_color_line(char *line, char *line_origin,
									int fd, t_map_data *map_data)
{
	if (line[0] != ' ')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_MISSING_COLOR_VALUE, map_data);
	}
}

void	get_floor_color(char *line, t_map_data *map_data,
							int fd, char *line_origin)
{
	char	*rgb_str_sanitized;

	if (map_data->is_floor_already_defined == 1)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_DUPLICATE_COLOR, map_data);
	}
	validate_color_line(line, line_origin, fd, map_data);
	rgb_str_sanitized = ft_strtrim(line + 1, " \t\n\r\v\f");
	if (rgb_str_sanitized == NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	if (parse_rgb_values(rgb_str_sanitized, map_data, "floor") == -1)
	{
		free(rgb_str_sanitized);
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_INVALID_RGB, map_data);
	}
	free(rgb_str_sanitized);
	map_data->is_floor_already_defined = 1;
}

void	get_ceiling_color(char *line, t_map_data *map_data,
							int fd, char *line_origin)
{
	char	*rgb_str_sanitized;

	if (map_data->is_ceiling_already_defined == 1)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_DUPLICATE_COLOR, map_data);
	}
	validate_color_line(line, line_origin, fd, map_data);
	rgb_str_sanitized = ft_strtrim(line + 1, " \t\n\r\v\f");
	if (rgb_str_sanitized == NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	if (parse_rgb_values(rgb_str_sanitized, map_data, "ceiling") == -1)
	{
		free(rgb_str_sanitized);
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_INVALID_RGB, map_data);
	}
	free(rgb_str_sanitized);
	map_data->is_ceiling_already_defined = 1;
}
