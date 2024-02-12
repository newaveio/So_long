/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:42:21 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 22:43:00 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_map(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (y < data->game->rows)
	{
		x = 0;
		while (x < data->game->cols)
		{
			if (data->game->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tile_text[0], x * TILE_SIZE, y * TILE_SIZE);
			if (data->game->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall_text[0], x * TILE_SIZE, y * TILE_SIZE);
			if (data->game->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_text[0], x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	ft_update_map(t_data *data, int old_x, int old_y)
{
	if (old_x != 0 || old_y != 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tile_text[0], old_x * TILE_SIZE, old_y * TILE_SIZE); // tiles
	draw_moves(data);
}