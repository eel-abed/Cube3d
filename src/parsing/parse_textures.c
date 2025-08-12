/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:12:56 by eel-abed          #+#    #+#             */
/*   Updated: 2025/05/03 19:40:41 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

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
		printf("Error\nInvalid texture format: %s\n", line);
		ft_free_tab(split);
		return (1);
	}
	// Vérifier si la texture a déjà été définie
	if (*dest)
	{
		printf("Error\nTexture already defined\n");
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
