/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:37:51 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/30 15:09:18 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	flood_fill(char **copy, int x, int y, t_map *map)
{
	int	height;
	int	width;

	height = map->height;
	width = map->width;
	if (x < 0 || y < 0 || y >= height || x >= width)
		return ;
	if (copy[y][x] == '1' || copy[y][x] == 'x')
		return ;
	copy[y][x] = 'x';
	flood_fill(copy, x + 1, y, map);
	flood_fill(copy, x - 1, y, map);
	flood_fill(copy, x, y + 1, map);
	flood_fill(copy, x, y - 1, map);
}

static void	free_copy(char **copy)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

int	check_playability(char **copy, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'P')
				flood_fill(copy, x, y, map);
			x++;
		}
		y++;
	}
	y = 0;
	if (check_playability_helper(copy) == 0)
		return (free_copy(copy), 0);
	else
		return (free_copy(copy), 1);
}

int	check_playability_helper(char **copy)
{
	int	x;
	int	y;

	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

char	**get_copy(t_map *map, char *error)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
	{
		perror("malloc failed");
		*error = MALLOC_ERROR;
		return (NULL);
	}
	y = 0;
	while (y < map->height)
	{
		copy[y] = ft_strdup(map->lines[y]);
		if (!copy[y])
			return (free_copy(copy), *error = MALLOC_ERROR, NULL);
		y++;
	}
	copy[y] = NULL;
	return (copy);
}
