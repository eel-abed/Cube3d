/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:12:56 by eel-abed          #+#    #+#             */
/*   Updated: 2025/08/25 16:48:06 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

int	validate_texture_file(char *path)
{
	int		fd;
	int		len;

	// Vérifier l'extension .xpm
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("Error\nTexture file must have .xpm extension: %s\n", path);
		return (1);
	}
	// Vérifier que le fichier existe et est lisible
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open texture file: %s\n", path);
		return (1);
	}
	close(fd);
	return (0);
}

int	parse_texture(char **dest, char *line)
{
	char	**split;
	int		len;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	// Compter le nombre d'éléments
	len = 0;
	while (split[len])
		len++;
	// Vérifier le format (2 éléments: identifiant et chemin)
	if (len != 2)
	{
		printf("Error\nInvalid texture format: %s", line);
		ft_free_tab(split);
		return (1);
	}
	// Vérifier si la texture a déjà été définie
	if (*dest)
	{
		printf("Error\nTexture %s already defined\n", split[0]);
		ft_free_tab(split);
		return (1);
	}
	// Nettoyer le chemin (enlever le newline si présent)
	len = ft_strlen(split[1]);
	if (len > 0 && split[1][len - 1] == '\n')
		split[1][len - 1] = '\0';
	// Valider le fichier texture
	if (validate_texture_file(split[1]) != 0)
	{
		ft_free_tab(split);
		return (1);
	}
	// Allouer et copier le chemin de la texture
	*dest = ft_strdup(split[1]);
	ft_free_tab(split);
	if (!*dest)
		return (1);
	return (0);
}
