/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:34:15 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 14:36:33 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_;
	size_t			i;

	s_ = (unsigned char *) s;
	i = 0;
	if (!s || n == 0)
		return ;
	while (n--)
	{
		*s_++ = '\0';
	}
}
