/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:09:08 by mbest             #+#    #+#             */
/*   Updated: 2024/02/01 16:52:44 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	surrounded_by_walls(char **map, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_nl(map[i]);
	while (i < len)
	{
		if (map[0][i] != '1' || map[data->game->rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < data->game->rows)
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_rectangular(char **map, t_data *data)
{
	int	i;
	int	len_first_line;

	i = 0;
	len_first_line = -1;
	while (i < data->game->rows)
	{
		if (len_first_line == -1)
			len_first_line = ft_strlen_nl(map[i]);
		else if (ft_strlen_nl(map[i]) != len_first_line)
			return (perror("Map is not rectangular\n"), 0);
		i++;
	}
	return (1);
}

int	check_caracters(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->game->rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == '1' || map[i][j] == 'C'
				|| map[i][j] == 'E' || map[i][j] == 'P' || map[i][j] == 'X')
				{
					if (map[i][j] == 'E')
					{
						data->game->exit_x = j;
						data->game->exit_y = i;
					}
				j++;
				}
			else
				return (0); // Error occured
		}
		i++;
	}
	return (1);
}

int	check_map_info(t_data *data)
{
	if (data->game->nb_collectibles < 1)
		return (perror("No collectibles\n"), 0);
	if (data->game->nb_e != 1)
		return (perror("Must contain only 1 exit\n"), 0);
	if (data->game->nb_p != 1)
		return (perror("Must contain only 1 player\n"), 0);
	return (1);
}

void	get_c_e_p(char **map, t_data *data)
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
		while (map[i][++j])
		{
			if (map[i][j] == 'C')
				data->game->nb_collectibles++;
			if (map[i][j] == 'E')
				data->game->nb_e++;
			if (map[i][j] == 'P')
				data->game->nb_p++;
			if (map[i][j] == 'X')
				data->game->nb_x++;
		}
	}
}

void	fill_enemies(char **map, t_data *data)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	data->enemies = (t_enemies *)malloc(data->game->nb_x * sizeof(t_enemies));
	if (data->enemies == NULL)
		return ;
	while (i < data->game->rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'X')
			{
				data->enemies[index].x = j;
				data->enemies[index].y = i;
				index++;
			}
			j++;
		}
		i++;
	}
	// index = 0;
	// while (index < data->game->nb_x)
	// {
	// 	printf("enemie[%d].x = %d\n", index, data->enemies[index].x);
	// 	printf("enemie[%d].y = %d\n", index, data->enemies[index].y);
	// 	index++;
	// }
}

void	fill_mapping_collectibles(char **map, t_data *data)
{
	int i;
	int j;
	int index;

	i = -1;
	index = -1;
	data->collectibles = (t_col *)malloc(data->game->nb_collectibles * sizeof(t_col));
	if (data->collectibles == NULL)
		return ;
	while (++i < data->game->rows)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'C')
			{
				data->collectibles[++index].x = j;
				data->collectibles[index].y = i;
				data->collectibles[index].collected = (int *)malloc(sizeof(int));
				if (data->collectibles[index].collected == NULL)
					return ;
				*(data->collectibles[index].collected) = 0;
			}
		}
	}
	// index = 0;
	// while (index < data->game->nb_collectibles)
	// {
	// 	printf("collectible[%d] ---- x = %d\ty = %d\t collected = %d\n\n", index, data->collectibles[index].x, data->collectibles[index].y, *(data->collectibles[index].collected));
	// 	index++;
	// }
}

int	get_map_info(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_c_e_p(map, data);
	fill_enemies(map, data);
	fill_mapping_collectibles(map, data);
	if (!(check_map_info(data)))
		return (0);
	return (1);
}

void	fill_struct_player_map(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->game->flood = (t_flood *)malloc(sizeof(t_flood));
	// Do else where maybe ???
	if (data->game->flood == NULL)
		return ;
	while (i < data->game->rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
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
	data->game->flood->cols = ft_strlen_nl(map[0]) - 1;
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

char	**copy_map(char **map, int rows)
{
	int		i;
	int		len;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * rows);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		copy[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (copy[i] == NULL)
			return (ft_printf("Failed to allocate memory for map copy\n"),
				NULL);
		ft_strlcpy(copy[i], map[i], len + 1);
		i++;
	}
	return (copy);
}
/* Do some freeing for the mallocs if an error occurs */

int	is_map_valid(char **map, t_data *data)
{
	char **buffer_map_c;
	char **buffer_map_e;

	buffer_map_c = copy_map(map, data->game->rows);
	buffer_map_e = copy_map(map, data->game->rows);
	fill_struct_player_map(buffer_map_c, data);
	if (!(flood_fill_c(buffer_map_c, data->game->flood->x, data->game->flood->y,
				data)) || !(flood_fill_e(buffer_map_e, data->game->flood->x,
				data->game->flood->y, data)))
		return (ft_printf("Flood Fill Failed\n"), 0);
	data->game->map = copy_map(map, data->game->rows);
	return (1);
}