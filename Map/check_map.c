/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:04:54 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/30 14:57:42 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_map(t_map *map, char *error)
{
	char	**copy;

	check_symbols(map, error);
	if (*error != '0')
		return ;
	check_walls(map, error);
	if (*error != '0')
		return ;
	check_mandatory(map, error);
	if (!((map->height >= 3 && map->width >= 5)
			|| (map->height >= 5 && map->width >= 3)))
		*error = SIZE_ERROR;
	if (*error != '0')
		return ;
	copy = get_copy(map, error);
	if (check_playability(copy, map) == 0)
		*error = UNPLAYABLE;
}

void	check_mandatory(t_map *map, char *error)
{
	int	y;
	int	x;

	y = 0;
	while (map->lines[y])
	{
		x = 0;
		while (map->lines[y][x])
		{
			if (map->lines[y][x] == 'P')
				map->player++;
			if (map->lines[y][x] == 'C')
				map->collect++;
			if (map->lines[y][x] == 'E')
				map->exit++;
			x++;
		}
		y++;
	}
	check_mandatory_helper(map, error);
}

void	check_mandatory_helper(t_map *map, char *error)
{
	if (map->player != 1)
		*error = SPAWN_ERROR;
	if (map->collect < 1)
		*error = COUNT_ERROR;
	if (map->exit != 1)
		*error = EXIT_ERROR;
}

void	check_symbols(t_map *map, char *error)
{
	int		y;
	int		x;
	char	*allowed;

	allowed = "10PEC";
	y = 0;
	while (map->lines[y])
	{
		x = 0;
		while (map->lines[y][x])
		{
			if (!ft_strchr(allowed, map->lines[y][x]))
				*error = CHAR_ERROR;
			x++;
		}
		y++;
	}
}

void	check_walls(t_map *map, char *error)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		if (y == 0 || y == map->height - 1)
		{
			while (map->lines[y][x])
			{
				if (map->lines[y][x] != '1')
					*error = WALLS_ERROR;
				x++;
			}
		}
		else
		{
			if (map->lines[y][0] != '1' || map->lines[y][map->width - 1] != '1')
				*error = WALLS_ERROR;
		}
		y++;
	}
}
