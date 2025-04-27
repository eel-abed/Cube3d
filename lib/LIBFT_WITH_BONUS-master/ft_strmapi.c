/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:14:49 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 14:37:44 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*copie;
	int		i;

	i = 0;
	len = ft_strlen(s);
	copie = malloc(sizeof(char) * (len + 1));
	if (!copie)
		return (NULL);
	while (s[i])
	{
		copie[i] = f(i, s[i]);
		i++;
	}
	copie[i] = '\0';
	return (copie);
}
