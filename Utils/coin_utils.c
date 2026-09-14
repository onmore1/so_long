/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:51:25 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 14:20:50 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_pathes(t_game *game, int index)
{
	static char	*coin_pathes[] = {
		"assets/coin/coin_1.png",
		"assets/coin/coin_2.png",
		"assets/coin/coin_3.png",
		"assets/coin/coin_4.png",
		"assets/coin/coin_5.png",
		"assets/coin/coin_6.png",
		NULL
	};

	game->coins[index]->anim->pathes = coin_pathes;
	game->coins[index]->anim->count = 6;
	game->coins[index]->anim->current = 0;
	game->coins[index]->anim->delay = 170;
	pre_render(game, index);
}

void	pre_render(t_game *game, int index)
{
	int				i;
	mlx_texture_t	*tex;

	i = 0;
	game->coins[index]->anim->imgs = malloc(sizeof(mlx_image_t *) * 7);
	while (game->coins[index]->anim->pathes[i])
	{
		tex = mlx_load_png(game->coins[index]->anim->pathes[i]);
		if (!tex)
		{
			perror("loading texture failed");
			clean_up(game);
		}
		game->coins[index]->anim->imgs[i]
			= mlx_texture_to_image(game->mlx, tex);
		mlx_delete_texture(tex);
		i++;
	}
	game->coins[index]->anim->imgs[i] = NULL;
}

void	clean_up_coins(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->collect)
	{
		if (game->coins[i])
		{
			if (game->coins[i]->anim)
			{
				if (game->coins[i]->anim->imgs)
				{
					delete_imgs(game, &i);
					free(game->coins[i]->anim->imgs);
				}
				free(game->coins[i]->anim);
			}
			free(game->coins[i]);
		}
		i++;
	}
	free(game->coins);
}

void	delete_imgs(t_game *game, int *i)
{
	int	j;

	j = 0;
	while (j < game->coins[*i]->anim->count)
	{
		if (game->coins[*i]->anim->imgs[j])
			mlx_delete_image(game->mlx, game->coins[*i]->anim->imgs[j]);
		j++;
	}
}
