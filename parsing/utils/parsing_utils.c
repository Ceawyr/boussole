/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:14:07 by cnamoune          #+#    #+#             */
/*   Updated: 2025/08/08 02:14:07 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	put_space_everywhere(void *str, size_t n)
{
	unsigned char	*str_final;
	size_t			i;

	if (str == NULL)
		return ;
	str_final = (unsigned char *)str;
	i = 0;
	while (i < (n - 1))
	{
		str_final[i] = ' ';
		i++;
	}
	str_final[i] = '\0';
}

void	*malloc_filled_with_space(size_t nmemb, size_t size)
{
	void	*str;

	if (size != 0 && (nmemb > SIZE_MAX / size))
	{
		return (NULL);
	}
	str = (void *)malloc(size * nmemb);
	if (str == NULL)
	{
		return (NULL);
	}
	put_space_everywhere(str, (size * nmemb));
	return (str);
}

int	skip_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	return (i);
}

int	ft_atoi_with_validation(const char *nptr, int *is_valid)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	*is_valid = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			sign = sign * -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i++] - 48);
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && (-1 * result) < INT_MIN))
			return (*is_valid = 0, 0);
	}
	if (nptr[i] != '\0')
		*is_valid = 0;
	return (sign * result);
}

void	free_tab_rgb(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}
