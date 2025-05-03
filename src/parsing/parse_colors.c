/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/05/03 19:40:30 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_color(char *line, int *color_dest)
{
	char	**split;
	char	**rgb;

	int r, g, b;
	// Extraire la partie après l'identifiant
	split = ft_split(line, ' ');
	if (!split || !split[1])
		return (1);
	// Extraire les valeurs RGB
	rgb = ft_split(split[1], ',');
	ft_free_tab(split);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_tab(rgb);
		printf("Error\nInvalid RGB format\n");
		return (1);
	}
	// Convertir et vérifier les valeurs RGB
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
