/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:50:18 by mbest             #+#    #+#             */
/*   Updated: 2024/03/15 13:11:14 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(t_data *data)
{
	int		i;
	int		len;
	char	**copy;

	copy = (char **)ft_calloc(data->game->rows, sizeof(char *));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < data->game->rows)
	{
		len = ft_strlen(data->buf_map[i]);
		copy[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (copy[i] == NULL)
			return (ft_printf("Failed to allocate memory for data->buf_map copy\n"),
				NULL);
		ft_strlcpy(copy[i], data->buf_map[i], len + 1);
		i++;
	}
	return (copy);
}

int 	copy_map_bis(t_data *data)
{
	int		i;
	int		len;
	char	**copy;

	copy = (char **)ft_calloc(data->game->rows, sizeof(char *));
	if (copy == NULL)
		return (0);
	i = 0;
	while (i < data->game->rows)
	{
		len = ft_strlen(data->buf_map[i]);
		copy[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (copy[i] == NULL)
			return (ft_printf("Failed to allocate memory for copy[i]\n"),
				0);
		ft_strlcpy(copy[i], data->buf_map[i], len + 1);
		i++;
	}
	data->game->map = copy;
	return (1);
}

int	is_map_valid(t_data *data)
{
	char **buffer_map_c;
	char **buffer_map_e;

	buffer_map_c = copy_map(data);
	if (buffer_map_c == NULL)
		return (ft_printf("[is_map_valid] - Failed to allocate memory\n"), 0);
	buffer_map_e = copy_map(data);
	if (buffer_map_e == NULL)
		return (ft_printf("[is_map_valid] - Failed to allocate memory\n"), free_2d_array(buffer_map_c, data->game->rows), 0);
	fill_struct_player_map(data);
	if (!(flood_fill_c(buffer_map_c, data->game->flood->x, data->game->flood->y,
				data)) || !(flood_fill_e(buffer_map_e, data->game->flood->x,
				data->game->flood->y, data)))
		return (free_2d_array(buffer_map_c, data->game->rows), free_2d_array(buffer_map_e, data->game->rows), ft_printf("Flood Fill Failed\n"), 0);
	if (!(copy_map_bis(data)))
		return (ft_printf("Failed to copy buf_map to data->game->map\n"), free_2d_array(buffer_map_c, data->game->rows), free_2d_array(buffer_map_e, data->game->rows), 0);
	return (free_2d_array(buffer_map_c, data->game->rows), free_2d_array(buffer_map_e, data->game->rows), 1);
}

int	flood_fill_c(char **map, int x, int y, t_data *data)
{
	if (y < 0 || y >= data->game->flood->rows || x < 0
		|| x >= data->game->flood->cols || map[y][x] == '1' || map[y][x] == 'E'
		|| map[y][x] == 'X')
		return (0);
	if (map[y][x] == 'C')
		data->game->flood->collected++;
	map[y][x] = '1';
	if (data->game->flood->collected == data->game->nb_collectibles)
		return (1);
	if (flood_fill_c(map, x + 1, y, data) || flood_fill_c(map, x - 1, y, data)
		|| flood_fill_c(map, x, y + 1, data) || flood_fill_c(map, x, y - 1,
			data))
		return (1);
	return (0);
}

int	flood_fill_e(char **map, int x, int y, t_data *data)
{
	if (y < 0 || y >= data->game->flood->rows || x < 0
		|| x >= data->game->flood->cols || map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	if (map[y][x] == 'E')
		return (1);
	map[y][x] = '1';
	if (flood_fill_e(map, x + 1, y, data) || flood_fill_e(map, x - 1, y, data)
		|| flood_fill_e(map, x, y + 1, data) || flood_fill_e(map, x, y - 1,
			data))
		return (1);
	return (0);
}
