/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:04:08 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 14:20:50 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	key_handler(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.action != MLX_PRESS && key.action != MLX_REPEAT)
		return ;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (key.key == MLX_KEY_W || key.key == MLX_KEY_UP)
		move_player(game, 0, -1);
	else if (key.key == MLX_KEY_S || key.key == MLX_KEY_DOWN)
		move_player(game, 0, 1);
	else if (key.key == MLX_KEY_D || key.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0);
	else if (key.key == MLX_KEY_A || key.key == MLX_KEY_LEFT)
		move_player(game, -1, 0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int			tilex;
	int			tile_y;
	int			player_w;
	int			player_h;

	tilex = (game->player->x / 128) + dx;
	tile_y = (game->player->y / 128) + dy;
	player_w = 256;
	player_h = 126;
	if (!what_tile(game, game->map, tilex, tile_y))
		return ;
	game->player->x = tilex * 128 + 128 / 2 - player_w / 64;
	game->player->y = tile_y * 128 + 128 / 2 - player_h / 2;
	if (game->player->image->instances)
	{
		game->player->image->instances[0].x = game->player->x;
		game->player->image->instances[0].y = game->player->y;
		game->moves++;
		ft_printf("move count:%d\n", game->moves);
	}
	open_exit(game, tilex, tile_y);
}
