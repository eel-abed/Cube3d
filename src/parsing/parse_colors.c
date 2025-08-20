/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/08/20 17:09:18 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_color(char *line, int *color_dest)
{
	char	**split;
	char	**rgb;
	int		r, g, b;
	int		i;
	int		comma_count;
	
	split = ft_split(line, ' ');
	if (!split || !split[1])
		return (1);
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
	{
		ft_free_tab(split);
		printf("Error\nInvalid color format\n");
		return (1);
	}
	
	// virgule rgb
	comma_count = 0;
	i = 0;
	while (split[1][i])
	{
		if (split[1][i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
	{
		ft_free_tab(split);
		printf("Error\nInvalid RGB format - expected exactly 2 commas\n");
		return (1);
	}
	
	// extract rgb
	rgb = ft_split(split[1], ',');
	ft_free_tab(split);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_free_tab(rgb);
		printf("Error\nInvalid RGB format - missing values\n");
		return (1);
	}
	
	// 3 rgb verif
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		ft_free_tab(rgb);
		printf("Error\nInvalid RGB format - expected exactly 3 values\n");
		return (1);
	}
	
	// verif not empty
	if (rgb[0][0] == '\0' || rgb[1][0] == '\0' || rgb[2][0] == '\0' ||
		rgb[2][0] == '\n' || (rgb[2][0] == '\n' && rgb[2][1] == '\0'))
	{
		ft_free_tab(rgb);
		printf("Error\nEmpty or invalid RGB value\n");
		return (1);
	}
	
	// convert rgb
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
