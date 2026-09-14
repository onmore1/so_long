/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:46:50 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 14:22:36 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	render_map(t_game *game, t_map *map)
{
	int	x;
	int	y;
	int	tile_s;
	int	index;

	index = 0;
	tile_s = 128;
	y = 0;
	while (map->lines[y])
	{
		x = 0;
		while (map->lines[y][x])
		{
			render_tile(game, x, y, &index);
			x++;
		}
		y++;
	}
	render_coins(game);
	mlx_image_to_window(game->mlx,
		game->exit->image, game->exit->x, game->exit->y);
	mlx_image_to_window(game->mlx,
		game->player->image, game->player->x, game->player->y);
}

void	render_tile(t_game *game, int x, int y, int *index)
{
	int	tile_s;

	tile_s = 128;
	if (game->map->lines[y][x] == '1')
		render_sprite(game, "assets/map/wall1.png", tile_s * x, tile_s * y);
	else if (game->map->lines[y][x] == '0')
		render_sprite(game, "assets/map/floor.png", tile_s * x, tile_s * y);
	else if (game->map->lines[y][x] == 'P')
	{
		render_sprite(game, "assets/map/floor.png", tile_s * x, tile_s * y);
		game->player->x = 128 * x + (64 - tile_s);
		game->player->y = 128 * y + (128 - tile_s) / 2;
	}
	else
		render_tile_helper(game, x, y, index);
}

void	render_tile_helper(t_game *game, int x, int y, int *index)
{
	int	tile_s;
	int	px;
	int	py;

	tile_s = 128;
	if (game->map->lines[y][x] == 'C')
	{
		render_sprite(game, "assets/map/floor.png", tile_s * x, tile_s * y);
		game->coins[*index]->x = x * tile_s + (tile_s / 2) - (64 / 2);
		game->coins[*index]->y = y * tile_s + (tile_s / 2) - (57 / 2);
		(*index)++;
	}
	else if (game->map->lines[y][x] == 'E')
	{
		render_sprite(game, "assets/map/floor.png", tile_s * x, tile_s * y);
		px = 128 * x;
		py = 128 * y;
		game->exit->x = x * 128;
		game->exit->y = y * 128;
	}
}

void	render_sprite(t_game *game, char *path, int x, int y)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
	{
		perror("loading texture failed");
		ft_free(game);
		exit(EXIT_FAILURE);
	}
	img = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	if (mlx_image_to_window(game->mlx, img, x, y) < 0)
	{
		perror("Image render failed");
		ft_free(game);
		exit(EXIT_FAILURE);
	}
}

void	render_coins(t_game *game)
{
	int		index;
	int		j;
	t_anim	*anim;

	index = 0;
	while (index < game->map->collect)
	{
		anim = game->coins[index]->anim;
		j = 0;
		while (anim->imgs[j])
		{
			mlx_image_to_window(game->mlx,
				anim->imgs[j],
				game->coins[index]->x,
				game->coins[index]->y);
			anim->imgs[j]->instances[0].enabled = false;
			j++;
		}
		index++;
	}
}
