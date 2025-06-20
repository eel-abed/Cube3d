/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:53:51 by mafourni          #+#    #+#             */
/*   Updated: 2025/05/01 16:24:34 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_keep_line_clean(char *keep_line)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (keep_line[i] != '\n')
		i++;
	i++;
	j = i;
	i = 0;
	while (keep_line[j] != '\0')
		keep_line[i++] = keep_line[j++];
	keep_line[i] = '\0';
	return (keep_line);
}

char	*ft_get_that_line(char *keep_line)
{
	size_t	i;
	char	*line_clean;

	line_clean = NULL;
	i = 0;
	if (!keep_line)
		return (NULL);
	while (keep_line[i] != '\n')
		i++;
	i++;
	line_clean = malloc((sizeof(char) * i + 1));
	ft_strlcpy(line_clean, keep_line, i + 1);
	line_clean[i] = '\0';
	return (line_clean);
}

char	*ft_read_fd(int fd, char *keep_line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		check_read;

	check_read = 0;
	check_read = read(fd, buffer, BUFFER_SIZE);
	while (check_read > 0)
	{
		buffer[check_read] = '\0';
		if (!keep_line)
			keep_line = ft_strdup(buffer);
		else
			keep_line = ft_strjoin(keep_line, buffer);
		if (ft_strchr(keep_line, '\n') != 0)
			break ;
		check_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (keep_line);
}

char	*get_next_line(int fd)
{
	static char	*keep_line;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (free(keep_line), keep_line = NULL, NULL);
	keep_line = ft_read_fd(fd, keep_line);
	if (ft_strchr(keep_line, '\n') == 0)
	{
		if (ft_strlen(keep_line) == 0)
		{
			free(keep_line);
			keep_line = NULL;
		}
		return (line = keep_line, keep_line = NULL, line);
	}
	line = ft_get_that_line(keep_line);
	if (line[0] == '\n' && keep_line[1] == '\0')
	{
		if (keep_line != NULL)
			free(keep_line);
		keep_line = NULL;
	}
	else
		ft_keep_line_clean(keep_line);
	return (line);
}
