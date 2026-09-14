/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:40:47 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 14:22:36 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	update(void *param)
{
	t_game	*game;
	int		i;

	game = (t_game *)param;
	i = 0;
	while (i < game->map->collect)
	{
		if (game->coins[i] && game->coins[i]->show)
			run_anim(game, i);
		i++;
	}
}

void	run_anim(t_game *game, int i)
{
	t_anim	*anim;
	long	now;
	long	elapsed;
	int		prev;

	if (!game->coins[i] || !game->coins[i]->anim || !game->coins[i]->show)
		return ;
	anim = game->coins[i]->anim;
	now = get_time_ms();
	elapsed = now - game->coins[i]->last_upt;
	if (elapsed >= anim->delay)
	{
		prev = anim->current;
		anim->current++;
		if (anim->current >= anim->count)
			anim->current = 0;
		anim->imgs[prev]->instances[0].enabled = false;
		anim->imgs[anim->current]->instances[0].enabled = true;
		game->coins[i]->last_upt = now;
	}
	return ;
}
