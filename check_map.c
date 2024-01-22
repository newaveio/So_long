/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:09:08 by mbest             #+#    #+#             */
/*   Updated: 2024/01/22 20:26:26 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/headers/ft_printf.h"
#include "libft/headers/libft.h"

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

int	check_map_info(t_map map_info)
{
	if (map_info.nb_c < 1)
		return (perror("No collectibles\n"), 0);
	if (map_info.nb_e != 1)
		return (perror("Must contain only 1 exit\n"), 0);
	if (map_info.nb_p != 1)
		return (perror("Must contain only 1 player\n"), 0);
	return (1);
}

void	get_c_e_p(char **map, int rows, t_map *map_info)
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
	int		i;
	int		j;
	t_map	map_info;

	i = 0;
	j = 0;
	get_c_e_p(map, rows, &map_info);
	if (!(check_map_info(map_info)))
		return (0);
	return (1);
}

void    fill_struct_player_map(char **map, t_play *play_map_info, int rows)
{
    int i;
    int j;

    i = 0;
    j = 0;
    play_map_info->nb_c = 0;
    while (i < rows)
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
        i++;
    }
    play_map_info->rows = rows;
    play_map_info->cols = ft_strlen_nl(map[0]);
}

int flood_fill(char **map, t_play *play_map_info)
{

}

int	is_map_valid(char **map, int rows)
{
	t_play play_map_info;
	// int collected;
	// int exits;

    fill_struct_player_map(map, &play_map_info, rows);
    printf("Player Position X\t\t%d\n", play_map_info.player_x);
    printf("Player Position Y\t\t%d\n", play_map_info.player_y);
    printf("Number of collectibles\t\t%d\n", play_map_info.nb_c);
    printf("Number of rows\t\t%d\n", play_map_info.rows);
    printf("Number of cols\t\t%d\n", play_map_info.cols);

    return (flood_fill(map, &play_map_info));
}