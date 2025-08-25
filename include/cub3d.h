/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:30:29 by eel-abed          #+#    #+#             */
/*   Updated: 2025/08/25 16:48:08 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/Get_next_line/get_next_line.h"
# include "../lib/LIBFT_WITH_BONUS-master/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_player
{
	double x;
	double y;
	char orientation; //(N,S,E,W)
}		t_player;

typedef struct s_map
{
	char **grid;
	int width;
	int height;
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	int floor_color;
	int ceiling_color;
}		t_map;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_player player;
	t_map map;
}		t_game;

int		parse_map(t_game *game, char *file_path);


int		parse_textures_and_colors(t_game *game, int fd);
int		parse_texture(char **dest, char *line);
int		validate_texture_file(char *path);
int		parse_color(char *line, int *color_dest);
int		parse_map_grid(t_game *game, int fd, char *file_path);
int		validate_map(t_game *game);
int		validate_chars(t_game *game);
int		validate_walls(t_game *game);
int		is_valid_char(char c);
int		is_surrounded_by_walls(t_game *game, int y, int x);
int		check_file_extension(char *filename);
int		open_map_file(char *file_path);
int		is_map_line(char *line);
void	ft_free_tab(char **tab);
void	init_game(t_game *game);
void	clean_exit(t_game *game, int status);
//hooks pour fermer screen
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);

#endif
