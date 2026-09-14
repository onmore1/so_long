/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:42:24 by vananiev          #+#    #+#             */
/*   Updated: 2025/09/30 14:47:41 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/printf/ft_printf.h"
# include "libft/libft.h"
# include "sys/time.h"

enum e_errors
{
	SPAWN_ERROR = 1,
	COUNT_ERROR = 2,
	EXIT_ERROR = 3,
	LINES_ERROR = 4,
	MALLOC_ERROR = 5,
	CHAR_ERROR = 6,
	SIZE_ERROR = 7,
	WALLS_ERROR = 8,
	EMPTY_FILE = 9,
	UNPLAYABLE = 10
};

typedef struct s_anim
{
	char		**pathes;
	mlx_image_t	**imgs;
	int			count;
	int			current;
	int			x;
	int			y;
	int			delay;
}	t_anim;

typedef struct s_ent
{
	int			x;
	int			y;
	int			height;
	int			width;
	int			i;
	int			show;
	long long	last_upt;
	mlx_image_t	*image;
	t_anim		*anim;
}	t_ent;

typedef struct s_map
{
	char		**lines;
	int			width;
	int			height;
	int			player;
	int			collect;
	int			collected;
	int			exit;
	int			is_open;
}	t_map;

typedef struct s_game
{
	int				width;
	int				moves;
	int				height;
	int				coin_index;
	int				collected;
	long long		last_update;
	t_map			*map;
	mlx_t			*mlx;
	t_ent			*player;
	t_ent			*exit;
	t_ent			**coins;
}	t_game;

//Core Setup
int		main(int argc, char **argv);
int		so_long(char **argv);
void	get_map(t_game *game, t_map *map, char **argv, char *error);
void	init_map(t_game *game, t_map *map, char *error, char **argv);
void	fill_lines(t_game *game, t_map *map, char *error, char **argv);
void	fill_lines_helper(t_map *map, char *error, int fd);
void	init_caller(t_game *game);
char	**get_copy(t_map *map, char *error);

//Map Checking
void	check_map(t_map *map, char *error);
void	check_walls(t_map *map, char *error);
void	check_symbols(t_map *map, char *error);
void	check_mandatory(t_map *map, char *error);
int		check_playability(char **copy, t_map *map);
int		check_playability_helper(char **copy);
void	check_mandatory_helper(t_map *map, char *error);
void	flood_fill(char **copy, int x, int y, t_map *map);

//Error / Free
void	error_handler(char error, t_game *game);
void	ft_open(int *fd, char *file, t_game *game);
void	ft_free(t_game *game);
void	clean_up(t_game *game);
void	clean_up_coins(t_game *game);
void	delete_imgs(t_game *game, int *i);

//Rendering
int		what_tile(t_game *game, t_map *map, int tilex, int tile_y);
void	render_map(t_game *game, t_map *map);
void	render_tile(t_game *game, int x, int y, int *index);
void	render_tile_helper(t_game *game, int x, int y, int *index);
void	render_sprite(t_game *game, char *path, int x, int y);
void	render_coins(t_game *game);
void	print_counter(t_game *game);

//Initialization
void	init_window(t_game *game, t_map *map);
void	init_player(t_game *game);
void	init_exit(t_game *game);
void	init_coins(t_game *game);
void	init_coins_helper(t_game *game, int index);

//Gameplay
void	key_handler(mlx_key_data_t key, void *param);
void	move_player(t_game *game, int px, int py);
void	open_exit(t_game *game, int x, int y);
void	check_if_escape(t_game *game, int x, int y);
void	what_coin(t_game *game, int x, int y);
void	p_coins(t_game *game);

//Utils
void	free_frame_pathes(t_ent *ent);
void	turn_off(t_game *game, int *i);

//Bonus
void	load_pathes(t_game *game, int index);
void	pre_render(t_game *game, int index);
long	get_time_ms(void);
void	run_anim(t_game *game, int index);
void	update(void *param);
#endif
