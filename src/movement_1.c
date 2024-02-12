/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:35:49 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 22:39:04 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_move(t_data *data, int a)
{
	int flag;

	data->game->old_x = data->game->pos_x;
	data->game->old_y = data->game->pos_y;
	if (a == 1 || a == 3)
		flag = -1;
	else
		flag = 1;
	data->game->map[data->game->pos_y][data->game->pos_x] = '0';
	if (a == 3 || a == 4)
	{
		if (data->game->map[data->game->pos_y][data->game->pos_x+flag] == 'C')
		{
			collect(data, flag);
			data->game->collected++;
		}
		if (data->game->map[data->game->pos_y][data->game->pos_x+flag] == 'X')
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		if (data->game->map[data->game->pos_y][data->game->pos_x+flag] == 'E' && data->game->collected == data->game->nb_collectibles)
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		data->game->map[data->game->pos_y][data->game->pos_x+flag] = 'P';
		data->game->pos_x += flag;
		data->game->moves++;
	}
	else
	{
		if (data->game->map[data->game->pos_y+flag][data->game->pos_x] == 'C')
		{
			collect(data, flag);
			data->game->collected++;
		}
		if (data->game->map[data->game->pos_y+flag][data->game->pos_x] == 'X')
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		if (data->game->map[data->game->pos_y+flag][data->game->pos_x] == 'E' && data->game->collected == data->game->nb_collectibles)
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		data->game->map[data->game->pos_y+flag][data->game->pos_x] = 'P';
		data->game->pos_y += flag;
		data->game->moves++;
	}
	print_map(data);
}

int		mvt_checker(t_data *data, int a)
{
	int x;
	int y;
	int flag;

	x = data->game->pos_x;
	y = data->game->pos_y;
	if (a == 1 || a == 3)
		flag = -1;
	else
		flag = 1;
	if (a == 3 || a == 4)
	{
		if (data->game->map[y][x+flag] != '1' && data->game->map[y][x+flag] != 'E')
			return (1);
		if (data->game->map[y][x+flag] == 'E' && data->game->collected == data->game->nb_collectibles)
			return (1);
		else
			return (print_map(data), 0);
	}
	else
	{
		if (data->game->map[y+flag][x] != '1' && data->game->map[y+flag][x] != 'E')
			return (1);
		if (data->game->map[y+flag][x] == 'E' && data->game->collected == data->game->nb_collectibles)
			return (1);
		else
			return (print_map(data), 0);
	}
}
/* int a ----- 1 = up ---- 2 = down ---- 3 = left ---- 4 = right */
