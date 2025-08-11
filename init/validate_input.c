/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:38:13 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/10 18:38:13 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_cub_file(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (ext == NULL || ext == str)
		return (1);
	if (ft_strcmp(ext, ".cub") == 0)
		return (0);
	return (1);
}

void	validate_input(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(2, ERROR_ARGC, ft_strlen(ERROR_ARGC));
		exit(1);
	}
	if (is_cub_file(argv[1]) == 1)
	{
		write(2, ERROR_CUB, ft_strlen(ERROR_CUB));
		exit(1);
	}
}
