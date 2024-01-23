/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:35 by mbest             #+#    #+#             */
/*   Updated: 2024/01/23 19:39:35 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	mvt_ud(t_data *data)
{
	(void)data;
}

void	mvt_lr(t_data *data)
{
	(void)data;
}

int	on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\n", keysym);
	if (keysym == 65362 || keysym == 65364)
		mvt_ud(data);
	if (keysym == 65363 || keysym == 65361)
		mvt_lr(data);
	if (keysym == 65307)
		return (on_destroy(data));
	return (0);
}
/* 65362 up - 65364 down - 65363 left - 65361 right - 65307 esc */

int on_destroy(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}

void    fill_game_struct(t_game *g_data, char **map, int rows)
{
    g_data->collected = 0;
    g_data->moves = 0;
    // g_data->nb_collectibles = // Find a way to pass this info
    // Malloc the g_data->map and copy
}
/* Not finished yet */