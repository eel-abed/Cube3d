/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:41:57 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/24 12:46:58 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict	dst, const void *restrict src, size_t n)
{
	unsigned char	*dst_;
	unsigned char	*src_;

	dst_ = (unsigned char *) dst;
	src_ = (unsigned char *) src;
	if (n == 0)
		return (dst);
	if (!dst || !src)
		return (NULL);
	while (n--)
	{
		*dst_++ = *src_++;
	}
	return (dst);
}
