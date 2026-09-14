/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:08:22 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 14:22:45 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_window(t_game *game, t_map *map)
{
	game->width = 128 * map->width;
	game->height = 128 * map->height;
	game->moves = 0;
	game->last_update = get_time_ms();
	game->mlx = mlx_init(game->width, game->height, "So long", false);
	if (!game->mlx)
	{
		perror("MLX42 init failed");
		ft_free(game);
		exit(EXIT_FAILURE);
	}
}

void	init_player(t_game *game)
{
	mlx_texture_t	*tex;

	game->player = malloc(sizeof(t_ent));
	if (!game->player)
	{
		perror("malloc player failed");
		exit(EXIT_FAILURE);
	}
	tex = mlx_load_png("assets/idle/idle1.png");
	if (!tex)
	{
		perror("loading player texture failed");
		exit(EXIT_FAILURE);
	}
	game->player->image = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	game->player->height = 126;
	game->player->width = 256;
	game->player->anim = NULL;
	game->player->show = 0;
	game->player->last_upt = 0;
}

void	init_exit(t_game *game)
{
	mlx_texture_t	*tex;

	game->exit = malloc(sizeof(t_ent));
	if (!game->exit)
	{
		perror("malloc for exit failed");
		exit(EXIT_FAILURE);
	}
	tex = mlx_load_png("assets/map/exit.png");
	if (!tex)
	{
		perror("loading exit texture failed");
		exit(EXIT_FAILURE);
	}
	game->exit->image = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	game->exit->height = 128;
	game->exit->width = 128;
	game->exit->anim = NULL;
	game->exit->show = 0;
	game->exit->last_upt = 0;
}

void	init_coins(t_game *game)
{
	int	index;

	index = 0;
	game->coins = malloc(sizeof(t_ent *) * game->map->collect);
	if (!game->coins)
	{
		perror("malloc for coins failed");
		exit(EXIT_FAILURE);
	}
	while (index < game->map->collect)
	{
		init_coins_helper(game, index);
		game->coins[index]->height = 57;
		game->coins[index]->width = 64;
		game->coins[index]->x = 0;
		game->coins[index]->y = 0;
		game->coins[index]->i = index;
		game->coins[index]->image = NULL;
		game->coins[index]->show = 1;
		game->coins[index]->last_upt = get_time_ms();
		index++;
	}
}

void	init_coins_helper(t_game *game, int index)
{
	game->coins[index] = malloc(sizeof(t_ent));
	if (!game->coins[index])
	{
		perror("malloc coin entity failed");
		exit(EXIT_FAILURE);
	}
	game->coins[index]->anim = malloc(sizeof(t_anim));
	if (!game->coins[index]->anim)
	{
		perror("malloc coin anim failed");
		exit(EXIT_FAILURE);
	}
	load_pathes(game, index);
}
