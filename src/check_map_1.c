/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:09:08 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 22:53:49 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	surrounded_by_walls(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_nl(data->buf_map[i]);
	while (i < len)
	{
		if (data->buf_map[0][i] != '1' || data->buf_map[data->game->rows - 1][i] != '1')
			return (ft_printf("Map must be surrounded by walls\n"), 0);
		i++;
	}
	i = 0;
	while (i < data->game->rows)
	{
		if (data->buf_map[i][0] != '1' || data->buf_map[i][len - 1] != '1')
			return (ft_printf("Map must be surrounded by walls\n"), 0);
		i++;
	}
	return (1);
}

int	is_rectangular(t_data *data)
{
	int	i;
	int	len_first_line;

	i = 0;
	len_first_line = -1;
	while (i < data->game->rows)
	{
		if (len_first_line == -1)
			len_first_line = ft_strlen_nl(data->buf_map[i]);
		else if (ft_strlen_nl(data->buf_map[i]) != len_first_line)
			return (ft_printf("Map is not rectangular\n"), 0);
		i++;
	}
	return (1);
}

int	check_caracters(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->game->rows)
	{
		j = 0;
		while (data->buf_map[i][j])
		{
			if (data->buf_map[i][j] == '0' || data->buf_map[i][j] == '1' || data->buf_map[i][j] == 'C'
				|| data->buf_map[i][j] == 'E' || data->buf_map[i][j] == 'P' || data->buf_map[i][j] == 'X')
				{
					if (data->buf_map[i][j] == 'E')
					{
						data->game->exit_x = j;
						data->game->exit_y = i;
					}
				j++;
				}
			else
				return (ft_printf("Maps must only contain these 6 caracters : [0 - 1 - C - P - E - X]\n"), 0);
		}
		i++;
	}
	return (1);
}

int	check_map_info(t_data *data)
{
	if (data->game->nb_collectibles < 1)
		return (ft_printf("No collectibles\n"), 0);
	if (data->game->nb_e != 1)
		return (ft_printf("Must contain only 1 exit\n"), 0);
	if (data->game->nb_p != 1)
		return (ft_printf("Must contain only 1 player\n"), 0);
	return (1);
}

