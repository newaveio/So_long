/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:09:08 by mbest             #+#    #+#             */
/*   Updated: 2024/02/02 18:30:56 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	mapping_enemies(t_data *data)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	data->enemies = (t_enemies *)malloc(data->game->nb_x * sizeof(t_enemies));
	if (data->enemies == NULL)
		return (ft_printf("Malloc failled for data->enemies\n"), 0);
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
	data->collectibles[index].collected = (int *)malloc(sizeof(int));
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
	data->collectibles = (t_col *)malloc(data->game->nb_collectibles * sizeof(t_col));
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
				data->collectibles[index].collected = (int *)malloc(sizeof(int));
				if (!(mapping_collectibles_bis(data, index)))
					return (0);
			}
		}
	}
	return (1);
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
/*
1 - Retrieve info of the map (number of E, C, P, X)
2 - Check if there is the minimum requesites for playing
*/
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

char	**copy_map(t_data *data)
{
	int		i;
	int		len;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * data->game->rows);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < data->game->rows)
	{
		len = ft_strlen(data->buf_map[i]);
		copy[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (copy[i] == NULL)
			return (ft_printf("Failed to allocate memory for data->buf_map copy\n"),
				NULL);
		ft_strlcpy(copy[i], data->buf_map[i], len + 1);
		i++;
	}
	return (copy);
}
/* Do some freeing for the mallocs if an error occurs */

int 	copy_map_bis(t_data *data)
{
	int		i;
	int		len;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * data->game->rows);
	if (copy == NULL)
		return (0);
	i = 0;
	printf("OKOKOKOK 111111\n");
	while (i < data->game->rows)
	{
		printf("OKOKOKOK 2222222\n");
		len = ft_strlen(data->buf_map[i]);
		copy[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (copy[i] == NULL)
			return (ft_printf("Failed to allocate memory for copy[i]\n"),
				0);
		ft_strlcpy(copy[i], data->buf_map[i], len + 1);
		i++;
	}
	data->game->map = copy;
	return (1);
}

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
		return (ft_printf("Flood Fill Failed\n"), 0);
	// data->game->map = copy_map(data);
	if (!(copy_map_bis(data)))
		return (ft_printf("Failed to copy buf_map to data->game->map\n"), free_2d_array(buffer_map_c, data->game->rows), free_2d_array(buffer_map_e, data->game->rows), 0);
	// if (data->game->map == NULL)
	// 	return (ft_printf("Failed to copy buf_map to data->game->map\n"), free(buffer_map_c), free(buffer_map_e), 0);
	return (free_2d_array(buffer_map_c, data->game->rows), free_2d_array(buffer_map_e, data->game->rows), 1);
}
