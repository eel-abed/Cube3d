/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:50:21 by eel-abed          #+#    #+#             */
/*   Updated: 2025/04/27 18:03:35 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
	{
		return (0);
	}
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		return (0);
	}
	return (1);
}
static int	open_map_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR : Cannot open map file: %s\n", file_path);
		return (-1);
	}
	return (fd);
}
int	parse_map(t_game *game, char *file_path)
{
	int	fd;

	if (!check_file_extension(file_path))
	{
		printf("Error\nInvalid file extension: %s\n", file_path);
		return (1);
	}
	fd = open_map_file(file_path);
	if (fd == -1)
		return (1);
	if (parse_textures_and_colors(game, fd) != 0)
	{
		close(fd);
		return (1);
	}
	if (parse_map_grid(game, fd, file_path) != 0)
	{
		close(fd);
		return (1);
	}

	if (validate_map(game) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
