/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:20:54 by eel-abed          #+#    #+#             */
/*   Updated: 2025/05/01 15:59:16 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_map_lines(int fd)
{
	int		line_count;
	char	*line;

	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}
static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}
static int	allocate_map(t_game *game, int fd)
{
	int		height;
	char	*line;
	int		i;

	height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (is_map_line(line))
			height++;
		free(line);
	}
	if (height == 0)
	{
		printf("Error\nEmpty map\n");
		return (1);
	}
	game->map.grid = (char **)malloc(sizeof(char *) * (height + 1));
	if (!game->map.grid)
		return (1);
	for (i = 0; i <= height; i++)
		game->map.grid[i] = NULL;
	game->map.height = height;
	return (0);
}

int	parse_map_grid(t_game *game, int fd, char *file_path)
{
	char	*line;
	int		i;
	int		max_width;
	int		len;

	if (allocate_map(game, fd) != 0)
		return (1);
	close(fd);
	fd = open_map_file(file_path);
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (line[0] != '\n' && line[0] != '\0')
			i++;
		free(line);
	}
	i = 0;
	max_width = 0;
	while ((line = get_next_line(fd)) != NULL && i < game->map.height)
	{
		if (is_map_line(line))
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			game->map.grid[i] = ft_strdup(line);
			if (!game->map.grid[i])
			{
				free(line);
				return (1);
			}
			len = ft_strlen(game->map.grid[i]);
			if (len > max_width)
				max_width = len;
			i++;
		}
		free(line);
	}
	game->map.width = max_width;
	return (0);
}
