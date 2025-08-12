/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:10:00 by eel-abed          #+#    #+#             */
/*   Updated: 2025/05/03 19:43:51 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_game *game)
{
	// Initialiser tous les pointeurs à NULL
	ft_bzero(game, sizeof(t_game));
}

void	clean_exit(t_game *game, int status)
{
	int	i;

	// Libérer la mémoire de la grille
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	// Libérer les textures
	if (game->map.no_texture)
		free(game->map.no_texture);
	if (game->map.so_texture)
		free(game->map.so_texture);
	if (game->map.we_texture)
		free(game->map.we_texture);
	if (game->map.ea_texture)
		free(game->map.ea_texture);
	exit(status);
}

// Fonction pour afficher la carte (utile pour déboguer)
void	print_map(t_game *game)
{
	int	i;

	printf("Map dimensions: %d x %d\n", game->map.width, game->map.height);
	printf("Player position: (%.1f, %.1f) facing %c\n", game->player.x,
		game->player.y, game->player.orientation);
	printf("Textures: \n");
	printf("  NO: %s\n", game->map.no_texture);
	printf("  SO: %s\n", game->map.so_texture);
	printf("  WE: %s\n", game->map.we_texture);
	printf("  EA: %s\n", game->map.ea_texture);
	printf("Colors: \n");
	printf("  Floor: RGB(%d, %d, %d)\n", (game->map.floor_color >> 16) & 0xFF,
		(game->map.floor_color >> 8) & 0xFF, game->map.floor_color & 0xFF);
	printf("  Ceiling: RGB(%d, %d, %d)\n",
		(game->map.ceiling_color >> 16) & 0xFF,
		(game->map.ceiling_color >> 8) & 0xFF, game->map.ceiling_color & 0xFF);
	printf("Map grid:\n");
	i = 0;
	while (i < game->map.height)
	{
		printf("%s\n", game->map.grid[i]);
		i++;
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC key
		clean_exit(game, 0);
	return (0);
}

int	handle_close(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	init_game(&game);
	// Effectuer le parsing
	if (parse_map(&game, argv[1]) == 0)
	{
		printf("Parsing successful!\n");
		print_map(&game);
		// Point d'intégration pour votre coéquipier
		printf("\nParsing complete, ready for raycasting!\n");
	}
	else
	{
		printf("Parsing failed, exiting.\n");
		return (1);
	}
	clean_exit(&game, 0);
	return (0);
}
