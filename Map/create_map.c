/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:36:39 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 15:23:10 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	get_map(t_game *game, t_map *map, char **argv, char *error)
{
	init_map(game, map, error, argv);
	map->collect = 0;
	map->collected = 0;
	map->player = 0;
	map->exit = 0;
	map->is_open = 0;
	if (*error != '0')
		return ;
	fill_lines(game, map, error, argv);
	if (*error != '0')
		return ;
	check_map(map, error);
	if (*error != '0')
		return ;
}

void	init_map(t_game *game, t_map *map, char *error, char **argv)
{
	char	*line;
	int		fd;
	int		len;

	map->height = 0;
	map->width = 0;
	ft_open(&fd, argv[1], game);
	line = get_next_line(fd);
	if (line == NULL)
		*error = EMPTY_FILE;
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		if (map->height == 0)
			map->width = len;
		else if (len != map->width)
			*error = LINES_ERROR;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->lines = NULL;
}

void	fill_lines(t_game *game, t_map *map, char *error, char **argv)
{
	int		fd;

	ft_open(&fd, argv[1], game);
	map->lines = malloc(sizeof(char *) * (map->height + 1));
	if (!map->lines)
	{
		*error = MALLOC_ERROR;
		ft_free(game);
		return ;
	}
	fill_lines_helper(map, error, fd);
}

void	fill_lines_helper(t_map *map, char *error, int fd)
{
	char	*line;
	int		len;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		map->lines[y] = ft_strdup(line);
		free(line);
		if (!map->lines[y])
		{
			*error = MALLOC_ERROR;
			return ;
		}
		y++;
		line = get_next_line(fd);
	}
	get_next_line(-1);
	map->lines[y] = NULL;
	close(fd);
}
