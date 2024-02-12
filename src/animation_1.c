/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:33:03 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 23:33:51 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	animation_update(void *param)
{
	int opps_frame;
	int exit_frame;
	int col_frame;
	t_data *data;

	data = (t_data *)param;
	opps_frame = (data->anim_counter[0]++ / 5000) % 4;
	exit_frame = (data->anim_counter[1]++ / 4000) % 4 + 1;
	col_frame = (data->anim_counter[2]++ / 3000) % 4;
	anim_opps(data, opps_frame);
	anim_exit(data, exit_frame);
	anim_collectibles(data, col_frame);
	anim_player(data);
	return (0);
}

void	anim_exit(t_data *data, int frame)
{
	// printf("d-g-collected %d\n", data->game->collected);
	// printf("d-g-nb-collected")
	if (data->game->collected == data->game->nb_collectibles)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_text[frame], data->game->exit_x * TILE_SIZE, data->game->exit_y * TILE_SIZE);
}

void	anim_player(t_data *data)
{
	int frame;

	frame = 0;
	if (data->player_dir == -1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_text[1][0], data->game->pos_x * TILE_SIZE, data->game->pos_y * TILE_SIZE);
	else if (data->player_is_moving)
	{
		if (data->anim_counter[3] % 900 == 0)
		{
			frame = (data->anim_counter[3] / 900) % 8;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_text[data->player_dir][frame], data->game->pos_x * TILE_SIZE, data->game->pos_y * TILE_SIZE);
			if (frame == 7)
				data->player_is_moving = 0;
		}
		data->anim_counter[3]++;	
	}
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_text[data->player_dir][0], data->game->pos_x * TILE_SIZE, data->game->pos_y * TILE_SIZE);
}

void anim_opps(t_data *data, int frame)
{
	int i;

	i = 0;
	while (i < data->game->nb_x)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->opps_text[frame], data->enemies[i].x * TILE_SIZE, data->enemies[i].y * TILE_SIZE);
		i++;
	}
}

void	anim_collectibles(t_data *data, int frame)
{
	int i;

	i = 0;
	while (i < data->game->nb_collectibles)
	{
		if (*(data->collectibles[i].collected) == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collec_text[frame], data->collectibles[i].x * TILE_SIZE, data->collectibles[i].y * TILE_SIZE);
		i++;
	}	
}
