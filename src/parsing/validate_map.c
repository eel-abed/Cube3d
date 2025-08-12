/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:52 by eel-abed          #+#    #+#             */
/*   Updated: 2025/05/03 19:40:47 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	validate_chars(t_game *game)
{
	int	player_count;

	int i, j;
	player_count = 0;
	for (i = 0; i < game->map.height; i++)
	{
		for (j = 0; game->map.grid[i][j]; j++)
		{
			if (!is_valid_char(game->map.grid[i][j]))
			{
				printf("Error\nInvalid character in map: %c\n",
					game->map.grid[i][j]);
				return (1);
			}
			// Compter les positions du joueur
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				player_count++;
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player.orientation = game->map.grid[i][j];
			}
		}
	}
	if (player_count != 1)
	{
		printf("Error\nMap must have exactly one player starting position\n");
		return (1);
	}
	return (0);
}

int	is_surrounded_by_walls(t_game *game, int y, int x)
{
	// Si le caractère est un espace ou un mur, pas besoin de vérifier
	if (game->map.grid[y][x] == ' ' || game->map.grid[y][x] == '1')
		return (1);
	// Vérifier si la cellule est à la bordure
	if (y == 0 || y == game->map.height - 1 || x == 0
		|| x >= (int)ft_strlen(game->map.grid[y]) - 1)
		return (0);
	// Vérifier les cellules adjacentes
	if (y > 0 && (x >= (int)ft_strlen(game->map.grid[y - 1]) || game->map.grid[y
			- 1][x] == ' '))
		return (0);
	if (y < game->map.height - 1 && (x >= (int)ft_strlen(game->map.grid[y + 1])
			|| game->map.grid[y + 1][x] == ' '))
		return (0);
	if (game->map.grid[y][x - 1] == ' ')
		return (0);
	if (game->map.grid[y][x + 1] == ' ' || game->map.grid[y][x + 1] == '\0')
		return (0);
	return (1);
}

int	validate_walls(t_game *game)
{
	int i, j;
	for (i = 0; i < game->map.height; i++)
	{
		for (j = 0; game->map.grid[i][j]; j++)
		{
			// Vérifier uniquement les zones de jeu
			if (game->map.grid[i][j] == '0' || game->map.grid[i][j] == 'N'
				|| game->map.grid[i][j] == 'S' || game->map.grid[i][j] == 'E'
				|| game->map.grid[i][j] == 'W')
			{
				if (!is_surrounded_by_walls(game, i, j))
				{
					printf("Error\nMap is not surrounded by walls\n");
					return (1);
				}
			}
		}
	}
	return (0);
}

int	validate_map(t_game *game)
{
	if (validate_chars(game) != 0)
		return (1);
	if (validate_walls(game) != 0)
		return (1);
	return (0);
}
