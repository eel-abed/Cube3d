/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:30:29 by eel-abed          #+#    #+#             */
/*   Updated: 2025/04/27 14:40:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/LIBFT_WITH_BONUS-master/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/* Définitions de constantes */
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_SIZE 32

/* Structures de données */
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	t_map		map;
}				t_game;

/* Prototypes de fonctions */
// Parsing
int				parse_map(t_game *game, char *file_path);

// Rendering
void			raycasting(t_game *game);

// Game
int				handle_keypress(int keycode, t_game *game);
int				handle_close(t_game *game);

// Utils
void			init_game(t_game *game);
void			clean_exit(t_game *game, int status);

#endif
