/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:38:30 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 14:21:34 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	what_tile(t_game *game, t_map *map, int tilex, int tile_y)
{
	if (tilex + 1 < map->width && map->lines[tile_y][tilex + 1] == '1')
	{
		printf("You can not move into the wall❗\n");
		return (0);
	}
	if (tilex < map->width && map->lines[tile_y][tilex + 1] == 'C')
	{
		what_coin(game, tile_y, tilex + 1);
		game->map->lines[tile_y][tilex + 1] = '0';
		game->map->collected++;
		return (1);
	}
	return (1);
}

void	what_coin(t_game *game, int tile_y, int tilex)
{
	int		coin_tilex;
	int		coin_tile_y;
	int		i;
	int		collect;

	i = 0;
	collect = game->map->collect;
	while (i < collect)
	{
		if (game->coins[i])
		{
			coin_tilex = game->coins[i]->x / 128;
			coin_tile_y = game->coins[i]->y / 128;
			if (coin_tilex == tilex && coin_tile_y == tile_y)
			{
				turn_off(game, &i);
				break ;
			}
		}
		i++;
	}
}

void	turn_off(t_game *game, int *i)
{
	int	j;

	j = 0;
	while (j < game->coins[*i]->anim->count)
	{
		game->coins[*i]->anim->imgs[j]->instances[0].enabled = false;
		j++;
	}
	game->coins[*i]->show = 0;
}

void	open_exit(t_game *game, int x, int y)
{
	mlx_texture_t	*tex;
	int				exit_x;
	int				exit_y;

	exit_x = game->exit->x / 128 - 1;
	exit_y = game->exit->y / 128;
	check_if_escape(game, x, y);
	if (game->map->collected == game->map->collect && !game->map->is_open)
	{
		mlx_delete_image(game->mlx, game->exit->image);
		tex = mlx_load_png("assets/map/exit_open.png");
		if (!tex)
		{
			perror("loading exit texture failed");
			exit(EXIT_FAILURE);
		}
		game->exit->image = mlx_texture_to_image(game->mlx, tex);
		mlx_delete_texture(tex);
		mlx_image_to_window(game->mlx, game->exit->image,
			game->exit->x, game->exit->y);
		game->map->is_open = 1;
		ft_printf("EXIT IS OPEN 💥\n");
	}
}

void	check_if_escape(t_game *game, int x, int y)
{
	int	exit_x;
	int	exit_y;

	exit_x = game->exit->x / 128 - 1;
	exit_y = game->exit->y / 128;
	if (game->map->is_open && (exit_x == x && exit_y == y))
	{
		printf("You escaped!\n");
		mlx_close_window(game->mlx);
		clean_up(game);
	}
}
