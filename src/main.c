/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:30:29 by eel-abed          #+#    #+#             */
/*   Updated: 2025/04/27 14:53:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	// Initialiser la structure du jeu
	init_game(&game);
	// Initialiser la minilibX
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		printf("Error\nFailed to initialize MLX\n");
		return (1);
	}
	// Créer une fenêtre
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game.win)
	{
		printf("Error\nFailed to create window\n");
		free(game.mlx);
		return (1);
	}
	// Analyser la carte
	if (parse_map(&game, argv[1]) != 0)
	{
		clean_exit(&game, 1);
		return (1);
	}
	// Configurer les hooks (événements)
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	// Démarrer la boucle principale
	mlx_loop(game.mlx);
	return (0);
}
