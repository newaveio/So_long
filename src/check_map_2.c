/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:47:08 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 23:49:10 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_c_e_p(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->game->nb_collectibles = 0;
	data->game->nb_e = 0;
	data->game->nb_p = 0;
	data->game->nb_x = 0;
	while (++i < data->game->rows)
	{
		j = -1;
		while (data->buf_map[i][++j])
		{
			if (data->buf_map[i][j] == 'C')
				data->game->nb_collectibles++;
			if (data->buf_map[i][j] == 'E')
				data->game->nb_e++;
			if (data->buf_map[i][j] == 'P')
				data->game->nb_p++;
			if (data->buf_map[i][j] == 'X')
				data->game->nb_x++;
		}
	}
}

int	get_map_info(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_c_e_p(data);
	if (!(check_map_info(data)))
		return (0);
	if (!(mapping_enemies(data)))
		return (ft_printf("Error while mapping the enemies\n"), 0);
	if (!(mapping_collectibles(data)))
		return (ft_printf("Error mapping the collectibles\n"), 0);
	return (1);
}

int	mapping_enemies(t_data *data)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	data->enemies = (t_enemies *)ft_calloc(data->game->nb_x, sizeof(t_enemies));
	if (data->enemies == NULL)
		return (ft_printf("Calloc failled for data->enemies\n"), 0);
	while (i < data->game->rows)
	{
		j = 0;
		while (data->buf_map[i][j])
		{
			if (data->buf_map[i][j] == 'X')
			{
				data->enemies[index].x = j;
				data->enemies[index].y = i;
				index++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int mapping_collectibles_bis(t_data *data, int index)
{
	data->collectibles[index].collected = (int *)ft_calloc(1, sizeof(int));
	if (data->collectibles[index].collected == NULL)
		return (ft_printf("[mapping_collectibles] - Failled to allocate memory\n"), 0);
	*(data->collectibles[index].collected) = 0;
	return (1);
}

int	mapping_collectibles(t_data *data)
{
	int i;
	int j;
	int index;

	i = -1;
	index = -1;
	data->collectibles = (t_col *)ft_calloc(data->game->nb_collectibles, sizeof(t_col));
	if (data->collectibles == NULL)
		return (ft_printf("[data->collectibles] - Failled to allocate memory\n"), 0);
	while (++i < data->game->rows)
	{
		j = -1;
		while (data->buf_map[i][++j])
		{
			if (data->buf_map[i][j] == 'C')
			{
				data->collectibles[++index].x = j;
				data->collectibles[index].y = i;
				if (!(mapping_collectibles_bis(data, index)))
					return (0);
			}
		}
	}
	return (1);
}
