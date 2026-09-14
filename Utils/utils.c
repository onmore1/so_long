/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:12:36 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/30 15:02:09 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_handler(char error, t_game *game)
{
	if (error == SPAWN_ERROR)
		write(2, "Spawn place count needs to be 1\n", 32);
	if (error == COUNT_ERROR)
		write(2, "Amount of collectables can not be less than 1\n", 46);
	if (error == EXIT_ERROR)
		write(2, "There should be 1 exit\n", 23);
	if (error == LINES_ERROR)
		write(2, "Lines dont match the length\n", 28);
	if (error == MALLOC_ERROR)
		write(2, "Malloc failed\n", 15);
	if (error == CHAR_ERROR)
		write(2, "Invalid character in map structure\n", 35);
	if (error == SIZE_ERROR)
		write(2, "Map too small\n", 14);
	if (error == WALLS_ERROR)
		write(2, "Invalid walls\n", 15);
	if (error == EMPTY_FILE)
		write(2, "Empty file\n", 12);
	if (error == UNPLAYABLE)
		write(2, "The game is unplayable\n", 24);
	ft_free(game);
}

void	ft_free(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	if (game->map->lines)
	{
		i = 0;
		while (game->map->lines[i])
		{
			free(game->map->lines[i]);
			i++;
		}
		free(game->map->lines);
	}
	free(game->map);
	game->map = NULL;
}

void	ft_open(int *fd, char *file, t_game *game)
{
	int	i;

	i = 0;
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		perror(file);
		free(game->map);
		exit(EXIT_FAILURE);
	}
}

long	get_time_ms(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	clean_up(t_game *game)
{
	int	i;

	i = 0;
	if (game->player)
	{
		if (game->player->image)
			mlx_delete_image(game->mlx, game->player->image);
		free(game->player);
	}
	if (game->exit)
	{
		if (game->exit->image)
			mlx_delete_image(game->mlx, game->exit->image);
		free(game->exit);
	}
	clean_up_coins(game);
	ft_free(game);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}
