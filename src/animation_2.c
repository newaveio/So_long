/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:39:40 by mbest             #+#    #+#             */
/*   Updated: 2024/03/13 16:23:36 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_anim_counter(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->anim_counter[i] = 0;
		i++;
	}
}

void	draw_moves(t_data *data)
{
	char	*moves;
	char	*str_moves;
	char	*buffer;

	moves = ft_strdup("MOVES");
	str_moves = ft_itoa(data->game->moves);
	if (data->game->moves != 0)
	{
		buffer = ft_itoa(data->game->moves - 1);
		mlx_string_put(data->mlx_ptr, data->win_ptr, TILE_SIZE * 2.5,
			data->window->height + (EXTRA_HEIGHT * .5), 0x000000, buffer);
		free(buffer);
	}
	mlx_string_put(data->mlx_ptr, data->win_ptr, TILE_SIZE, data->window->height
		+ (EXTRA_HEIGHT * .5), 0xFFFFFF, moves);
	mlx_string_put(data->mlx_ptr, data->win_ptr, TILE_SIZE * 2.5,
		data->window->height + (EXTRA_HEIGHT * .5), 0xFFFFFF, str_moves);
	free(str_moves);
	free(moves);
}

void	collect(t_data *data, int flag)
{
	int	i;

	i = 0;
	while (i < data->game->nb_collectibles)
	{
		if ((data->collectibles[i].x == data->game->pos_x + flag
				&& data->collectibles[i].y == data->game->pos_y)
			|| (data->collectibles[i].x == data->game->pos_x
				&& data->collectibles[i].y == data->game->pos_y + flag))
		{
			*(data->collectibles[i].collected) = 1;
			break ;
		}
		i++;
	}
}

int	on_destroy(t_data *data)
{
	free_textures(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_if(data);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == 65362 || keysym == 65364)
		mvt_ud(data, keysym);
	if (keysym == 65361 || keysym == 65363)
		mvt_lr(data, keysym);
	if (keysym == 65307)
		return (on_destroy(data));
	ft_printf("Number of moves = %d\n", data->game->moves);
	ft_update_map(data, data->game->old_x, data->game->old_y);
	return (0);
}
/* 65362 up - 65364 down - 65361 left - 65363 right - 65307 esc */