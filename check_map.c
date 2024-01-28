/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:09:08 by mbest             #+#    #+#             */
/*   Updated: 2024/01/29 00:03:32 by mbest            ###   ########.fr       */
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
	// printf("HELLO WE IN RECTANGULAR\n");
	while (i < data->game->rows)
	{
		if (len_first_line == -1)
			len_first_line = ft_strlen_nl(map[i]);
		else if (ft_strlen_nl(map[i]) != len_first_line)
			return (perror("Map is not rectangular\n"), 0);
		// printf("len first line = %d\n", len_first_line);
		// printf("len line = %d\n", ft_strlen_nl(map[i]));
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
				|| map[i][j] == 'E' || map[i][j] == 'P')
				j++;
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

	i = 0;
	j = 0;
	data->game->nb_collectibles = 0;
	data->game->nb_e = 0;
	data->game->nb_p = 0;
	while (i < data->game->rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				data->game->nb_collectibles++;
			if (map[i][j] == 'E')
				data->game->nb_e++;
			if (map[i][j] == 'P')
				data->game->nb_p++;
			j++;
		}
		i++;
	}
}

int	get_map_info(char **map, t_data *data)
{
	int			i;
	int			j;
	// t_map_ch	map_info;

	i = 0;
	j = 0;
	get_c_e_p(map, data);
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
	data->game->flood = (t_flood *)malloc(sizeof(t_flood)); // Do else where maybe ???
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

int	flood_fill(char **map, int x, int y, t_data *data)
{
	if (y < 0 || y >= data->game->flood->rows || x < 0 || x >= data->game->flood->cols
		|| map[y][x] == '1')
		return (0);
	if (map[y][x] == 'C')
		data->game->flood->collected++;
	if (map[y][x] == 'E')
		data->game->flood->exits++;
	map[y][x] = '1';
	if (data->game->flood->collected == data->game->nb_collectibles
		&& data->game->flood->exits == 1)
		return (1);
	if (flood_fill(map, x + 1, y, data) ||
		flood_fill(map, x - 1, y, data) ||
		flood_fill(map, x, y + 1, data) ||
		flood_fill(map, x, y - 1, data))
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
	char **buffer_map;

	buffer_map = copy_map(map, data->game->rows);
	fill_struct_player_map(buffer_map, data);
	if (!(flood_fill(buffer_map, data->game->flood->x, data->game->flood->y,
				data)))
		return (ft_printf("Flood Fill Failed\n"), 0);
	data->game->map = copy_map(map, data->game->rows);
	return (1);
}