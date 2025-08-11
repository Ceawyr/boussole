/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:12:56 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:12:56 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_north_texture_path(char *line, t_map_data *map_data,
								int fd, char *line_origin)
{
	if (map_data->north_texture_path != NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_DUPLICATE_TEXTURE, map_data);
	}
	if (line[0] != ' ')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_MISSING_TEXTURE_PATH, map_data);
	}
	map_data->north_texture_path = ft_strtrim(line + 1, " \t\n\r\v\f");
	if (map_data->north_texture_path == NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	if (map_data->north_texture_path[0] == '\0')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_TEXTURE_PATH_EMPTY, map_data);
	}
}

void	get_south_texture_path(char *line, t_map_data *map_data,
								int fd, char *line_origin)
{
	if (map_data->south_texture_path != NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_DUPLICATE_TEXTURE, map_data);
	}
	if (line[0] != ' ')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_MISSING_TEXTURE_PATH, map_data);
	}
	map_data->south_texture_path = ft_strtrim(line + 1, " \t\n\r\v\f");
	if (map_data->south_texture_path == NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	if (map_data->south_texture_path[0] == '\0')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_TEXTURE_PATH_EMPTY, map_data);
	}
}

void	get_west_texture_path(char *line, t_map_data *map_data, int fd,
								char *line_origin)
{
	if (map_data->west_texture_path != NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_DUPLICATE_TEXTURE, map_data);
	}
	if (line[0] != ' ')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_MISSING_TEXTURE_PATH, map_data);
	}
	map_data->west_texture_path = ft_strtrim(line + 1, " \t\n\r\v\f");
	if (map_data->west_texture_path == NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	if (map_data->west_texture_path[0] == '\0')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_TEXTURE_PATH_EMPTY, map_data);
	}
}

void	get_east_texture_path(char *line, t_map_data *map_data,
								int fd, char *line_origin)
{
	if (map_data->east_texture_path != NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_DUPLICATE_TEXTURE, map_data);
	}
	if (line[0] != ' ')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_MISSING_TEXTURE_PATH, map_data);
	}
	map_data->east_texture_path = ft_strtrim(line + 1, " \t\n\r\v\f");
	if (map_data->east_texture_path == NULL)
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_ALLOC, map_data);
	}
	if (map_data->east_texture_path[0] == '\0')
	{
		free(line_origin);
		clear_remaining_lines_gnl(fd);
		write_close_and_exit(fd, ERROR_TEXTURE_PATH_EMPTY, map_data);
	}
}
