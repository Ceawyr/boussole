/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:14:19 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:14:19 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clear_remaining_lines_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd, 0);
	}
}

void	free_residual_line_and_gnl(int fd, char **line)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	clear_remaining_lines_gnl(fd);
}

void	free_map_copy(char **map_copy)
{
	int	i;

	i = 0;
	while (map_copy[i] != NULL)
		free(map_copy[i++]);
	free(map_copy);
}

void	write_close_and_exit(int fd, const char *str, t_map_data *map_data)
{
	close(fd);
	write(2, str, ft_strlen(str));
	free_map_data(map_data);
	exit(1);
}
