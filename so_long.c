/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:42:29 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/29 15:25:50 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	so_long(char **argv)
{
	t_game	game;
	char	error;

	error = '0';
	game.map = malloc(sizeof(t_map));
	if (!game.map)
	{
		perror("malloc map failed");
		ft_free(&game);
		exit(EXIT_FAILURE);
	}
	get_map(&game, game.map, argv, &error);
	if (error != '0')
		return (error_handler(error, &game), 0);
	init_caller(&game);
	render_map(&game, game.map);
	mlx_key_hook(game.mlx, key_handler, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	clean_up(&game);
	return (0);
}

void	init_caller(t_game *game)
{
	init_window(game, game->map);
	init_player(game);
	init_coins(game);
	init_exit(game);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Invalid argument count\n", 23);
		exit(EXIT_FAILURE);
	}
	so_long(argv);
	return (0);
}
