/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:12:59 by eel-abed          #+#    #+#             */
/*   Updated: 2025/08/20 17:19:13 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


int	parse_textures_and_colors(t_game *game, int fd)
{
	char	*line;
	int		textures_found;

	textures_found = 0;
	// Initialiser les pointeurs de texture
	game->map.no_texture = NULL;
	game->map.so_texture = NULL;
	game->map.we_texture = NULL;
	game->map.ea_texture = NULL;
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	while (textures_found < 6 && (line = get_next_line(fd)) != NULL)
	{
		// Ignorer les lignes vides
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		// Traiter les différentes identifiants
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (parse_texture(&game->map.no_texture, line) == 0)
				textures_found++;
			else
			{
				free(line);
				return (1);
			}
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (parse_texture(&game->map.so_texture, line) == 0)
				textures_found++;
			else
			{
				free(line);
				return (1);
			}
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (parse_texture(&game->map.we_texture, line) == 0)
				textures_found++;
			else
			{
				free(line);
				return (1);
			}
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (parse_texture(&game->map.ea_texture, line) == 0)
				textures_found++;
			else
			{
				free(line);
				return (1);
			}
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (parse_color(line, &game->map.floor_color) == 0)
				textures_found++;
			else
			{
				free(line);
				return (1);
			}
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (parse_color(line, &game->map.ceiling_color) == 0)
				textures_found++;
			else
			{
				free(line);
				return (1);
			}
		}
		free(line);
	}
	// Vérifier que tous les éléments ont été trouvés
	if (textures_found < 6)
	{
		printf("Error\nMissing texture or color information\n");
		return (1);
	}
	return (0);
}

int	parse_map(t_game *game, char *file_path)
{
	int	fd;

	// Vérifier l'extension du fichier
	if (!check_file_extension(file_path))
	{
		printf("Error\nInvalid file extension: %s\n", file_path);
		return (1);
	}
	// Ouvrir le fichier
	fd = open_map_file(file_path);
	if (fd == -1)
		return (1);
	// Lire les textures et couleurs
	if (parse_textures_and_colors(game, fd) != 0)
	{
		close(fd);
		return (1);
	}
	// Lire la carte
	if (parse_map_grid(game, fd, file_path) != 0)
	{
		close(fd);
		return (1);
	}
	// Valider la carte
	if (validate_map(game) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
