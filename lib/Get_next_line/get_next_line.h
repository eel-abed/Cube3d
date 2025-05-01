/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:53:59 by mafourni          #+#    #+#             */
/*   Updated: 2025/05/01 15:56:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../LIBFT_WITH_BONUS-master/libft.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char		*get_next_line(int fd);
char		*ft_read_fd(int fd, char *keep_line);
char		*ft_get_that_line(char *keep_line);
char		*ft_keep_line_clean(char *keep_line);

#endif
