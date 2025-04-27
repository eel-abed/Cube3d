/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:20:29 by eel-abed          #+#    #+#             */
/*   Updated: 2025/04/27 17:29:03 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	// touche echape
	if (keycode == 65307)
		clean_exit(game, 0);
	// Autres touches à implémenter pour le mouvement
	return (0);
}

int	handle_close(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}
