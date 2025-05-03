/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:42 by eel-abed          #+#    #+#             */
/*   Updated: 2025/05/03 19:52:35 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	// Ignorer les espaces
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	// Si on trouve un '1' ou un '0', c'est une ligne de carte
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	parse_map_grid(t_game *game, int fd, char *file_path)
{
	char	*line;
	int		map_lines;
	int		len;

	int i, max_width = 0;
	// Compter le nombre de lignes de la carte
	map_lines = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_map_line(line))
			map_lines++;
		free(line);
	}
	// Vérifier si la carte est vide
	if (map_lines == 0)
	{
		printf("Error\nEmpty map\n");
		return (1);
	}
	// Allouer la mémoire pour la carte
	game->map.grid = (char **)malloc(sizeof(char *) * (map_lines + 1));
	if (!game->map.grid)
		return (1);
	game->map.height = map_lines;
	// Réouvrir le fichier pour lire la carte
	close(fd);
	fd = open_map_file(file_path);
	// Sauter les lignes jusqu'à la carte
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_map_line(line))
		{
			// Nettoyer la ligne (enlever le newline)
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			game->map.grid[i] = ft_strdup(line);
			// Mettre à jour la largeur maximale
			len = ft_strlen(game->map.grid[i]);
			if (len > max_width)
				max_width = len;
			i++;
		}
		free(line);
		if (i >= map_lines)
			break ;
	}
	game->map.grid[i] = NULL;
	game->map.width = max_width;
	return (0);
}
