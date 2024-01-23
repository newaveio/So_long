/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:09:08 by mbest             #+#    #+#             */
/*   Updated: 2024/01/23 14:45:31 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	surrounded_by_walls(char **map, int rows)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_nl(map[i]);
	printf("len = %d\n", len);
	while (i < len)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	// printf("Walls on first and last line\n");
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	// printf("Walls on first and last column\n");
	return (1);
}

int	is_rectangular(char **map, int rows)
{
	int	i;
	int	len_first_line;

	i = 0;
	len_first_line = -1;
	// printf("HELLO WE IN RECTANGULAR\n");
	while (i < rows)
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

int	check_caracters(char **map, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
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

int	check_map_info(t_map_ch map_info)
{
	if (map_info.nb_c < 1)
		return (perror("No collectibles\n"), 0);
	if (map_info.nb_e != 1)
		return (perror("Must contain only 1 exit\n"), 0);
	if (map_info.nb_p != 1)
		return (perror("Must contain only 1 player\n"), 0);
	return (1);
}

void	get_c_e_p(char **map, int rows, t_map_ch *map_info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_info->nb_c = 0;
	map_info->nb_e = 0;
	map_info->nb_p = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				map_info->nb_c++;
			if (map[i][j] == 'E')
				map_info->nb_e++;
			if (map[i][j] == 'P')
				map_info->nb_p++;
			j++;
		}
		i++;
	}
}

int	get_map_info(char **map, int rows)
{
	int			i;
	int			j;
	t_map_ch	map_info;

	i = 0;
	j = 0;
	get_c_e_p(map, rows, &map_info);
	if (!(check_map_info(map_info)))
		return (0);
	return (1);
}

void	fill_struct_player_map(char **map, t_play *play_map_info, int rows)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	play_map_info->nb_c = 0;
	while (++i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				play_map_info->nb_c++;
			if (map[i][j] == 'P')
			{
				play_map_info->player_x = i;
				play_map_info->player_y = j;
			}
			j++;
		}
	}
	play_map_info->collected = 0;
	play_map_info->exits = 0;
	play_map_info->rows = rows - 1;
	play_map_info->cols = ft_strlen_nl(map[0]) - 1;
}

int	flood_fill(char **map, int x, int y, t_play *play_map_info)
{
	if (x < 0 || x >= play_map_info->rows || y < 0 || y >= play_map_info->cols
		|| map[x][y] == '1')
		return (0);
	if (map[x][y] == 'C')
		play_map_info->collected++;
	if (map[x][y] == 'E')
		play_map_info->exits++;
	map[x][y] = '1';
	if (play_map_info->collected == play_map_info->nb_c
		&& play_map_info->exits == 1)
		return (1);
	if (flood_fill(map, x + 1, y, play_map_info) || // down
		flood_fill(map, x - 1, y, play_map_info) || // up
		flood_fill(map, x, y + 1, play_map_info) || // right
		flood_fill(map, x, y - 1, play_map_info))   // left
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

int	is_map_valid(char **map, int rows)
{
	t_play play_map_info;
	char **buffer_map;

	buffer_map = copy_map(map, rows);

	for (int i = 0; i < rows; i++)
	{
		ft_printf("Buffer Map\t%s\n", buffer_map[i]);
	}

	fill_struct_player_map(buffer_map, &play_map_info, rows);
	printf("\nPlayer Position X\t\t%d\n", play_map_info.player_x);
	printf("Player Position Y\t\t%d\n", play_map_info.player_y);
	printf("Number of collectibles\t\t%d\n", play_map_info.nb_c);
	printf("Number collected [counter]\t%d\n", play_map_info.collected);
	printf("Number exit [counter]\t\t%d\n", play_map_info.exits);
	printf("Number of rows\t\t\t%d\n", play_map_info.rows);
	printf("Number of cols\t\t\t%d\n\n", play_map_info.cols);

	if (!(flood_fill(buffer_map, play_map_info.player_x, play_map_info.player_y,
				&play_map_info)))
		return (ft_printf("Flood Fill Failed\n"), 0);
	for (int i = 0; i < rows; i++)
	{
		ft_printf("Buffer Map\t%s\n", buffer_map[i]);
	}
	printf("Flood fill OKKKKKKKKK\n\n");
	return (1);
}