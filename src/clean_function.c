/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:51:27 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 23:50:14 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_2d_array(char **map, int rows)
{
	int i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->game->rows)
	{
		free(data->game->map[i]);
		i++;
	}
	free(data->game->map);
}

void	free_structure(t_data *data)
{
	free_map(data);
}

void	free_if(t_data *data)
{
	int i;
	
	if (data->buf_map)
	{
		i = -1;
		while (++i < data->game->rows)
			free(data->buf_map[i]);
		free (data->buf_map);
	}
	if (data->collectibles)
	{
		i = -1;
		while (++i < data->game->nb_collectibles)
			free(data->collectibles[i].collected);
		free(data->collectibles);
	}
	if (data->enemies)
	{
		free(data->enemies);
	}
	if (data->game)
	{
		if (data->game->flood)
			free(data->game->flood);
		free(data->game);
	}
	if (data->window)
		free(data->window);
}
