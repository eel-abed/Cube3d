/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:00:29 by eel-abed          #+#    #+#             */
/*   Updated: 2025/04/27 17:27:36 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static int	validate_chars(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

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
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				player_count++;
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				if (game->map.grid[i][j] == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0;
				}
				else if (game->map.grid[i][j] == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0;
				}
				else if (game->map.grid[i][j] == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = 0.66;
				}
				else // 'W'
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = -0.66;
				}
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

static int	is_surrounded_by_walls(t_game *game, int y, int x)
{
	if (game->map.grid[y][x] == ' ' || game->map.grid[y][x] == '1')
		return (1);
	if (y == 0 || y == game->map.height - 1 || x == 0
		|| x >= (int)ft_strlen(game->map.grid[y]) - 1)
		return (0);
	if (x >= (int)ft_strlen(game->map.grid[y - 1]) || game->map.grid[y
		- 1][x] == ' ')
		return (0);
	if (x >= (int)ft_strlen(game->map.grid[y + 1]) || game->map.grid[y
		+ 1][x] == ' ')
		return (0);
	if (game->map.grid[y][x - 1] == ' ')
		return (0);
	if (game->map.grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	validate_walls(t_game *game)
{
	int	i;
	int	j;

	for (i = 0; i < game->map.height; i++)
	{
		for (j = 0; game->map.grid[i][j]; j++)
		{
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
