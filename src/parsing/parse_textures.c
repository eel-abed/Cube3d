/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:04:00 by eel-abed          #+#    #+#             */
/*   Updated: 2025/04/27 17:19:32 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	parse_texture(t_game *game, char **dest, char *line)
{
	char	**split;
	int		len;
	(void)game;

	split = ft_split(line, ' ');
	if (!split)
	{
		return (1);
	}
	len = 0;
	while (split[len])
	{
		len++;
	}
	if (len != 2)
	{
		printf("ERROR : Invalid texture format: %s\n", line);
		ft_free_tab(split);
		return (1);
	}
	if (*dest)
	{
		printf("Error\nTexture already defined\n");
		ft_free_tab(split);
		return (1);
	}
	*dest = ft_strdup(split[1]);
	ft_free_tab(split);
	if (!*dest)
		return (1);
	return (0);
}

static int	parse_color(char *line, int *color_dest)
{
	char	**split;
	char	**rgb;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ' ');
	if (!split || !split[1])
		return (1);
	rgb = ft_split(split[1], ',');
	ft_free_tab(split);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_tab(rgb);
		printf("Error\nInvalid RGB format\n");
		return (1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_tab(rgb);
		printf("Error\nRGB values must be between 0 and 255\n");
		return (1);
	}
	*color_dest = (r << 16) | (g << 8) | b;
	ft_free_tab(rgb);
	return (0);
}
int	parse_textures_and_colors(t_game *game, int fd)
{
	char	*line;
	int		textures_found;

	textures_found = 0;
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
		// Traiter les différents types d'éléments
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (parse_texture(game, &game->map.no_texture, line) == 0)
				textures_found++;
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (parse_texture(game, &game->map.so_texture, line) == 0)
				textures_found++;
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (parse_texture(game, &game->map.we_texture, line) == 0)
				textures_found++;
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (parse_texture(game, &game->map.ea_texture, line) == 0)
				textures_found++;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (parse_color(line, &game->map.floor_color) == 0)
				textures_found++;
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (parse_color(line, &game->map.ceiling_color) == 0)
				textures_found++;
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
