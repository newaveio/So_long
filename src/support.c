/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:35 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 23:29:34 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fill_data_struct(t_data *data)
{
	data->game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (data->game == NULL)
		return (ft_printf("[data->game] - Failled to allocate memory\n"), 0);
	data->game->flood = (t_flood *)ft_calloc(1, sizeof(t_flood));
	if (data->game->flood == NULL)
		return (ft_printf("[data->game->flood] - Failled to allocate memory\n"), 0);
	data->window = (t_window *)ft_calloc(1, sizeof(t_window));
	if (data->window == NULL)
		return (ft_printf("[data->window] - Failled to allocate memory\n"), 0);
	data->player_dir = -1;
	data->game->rows = 0;
	data->game->collected = 0;
	return (1);
}

void    fill_game_struct(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
    data->game->collected = 0;
	data->game->cols = ft_strlen_nl(data->game->map[0]);
    data->game->moves = 0;
	data->window->width = data->game->cols * TILE_SIZE;
	data->window->height = data->game->rows * TILE_SIZE;
}

void	fill_struct_player_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->game->rows)
	{
		j = 0;
		while (data->buf_map[i][j])
		{
			if (data->buf_map[i][j] == 'P')
			{
				data->game->pos_y = i;
				data->game->flood->y = i;
				data->game->pos_x = j;
				data->game->flood->x = j;
			}
			j++;
		}
		i++;
	}
	data->game->flood->collected = 0;
	data->game->flood->exits = 0;
	data->game->flood->rows = data->game->rows - 1;
	data->game->flood->cols = ft_strlen_nl(data->buf_map[0]) - 1;
}
