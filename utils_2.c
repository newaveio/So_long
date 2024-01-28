/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:42:58 by mbest             #+#    #+#             */
/*   Updated: 2024/01/28 17:38:26 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_count_map_lines(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(MAP_FILE, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening the file\n"), 0); // Error occured
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		(data->game->rows)++;
	}
	close(fd);
	return (1);
}

char	**fill_map(int rows)
{
	int		i;
	int		fd;
	int		len;
    char    *line;
	char	**map;

	map = (char **)malloc(rows * sizeof(char *));
	if (map == NULL)
		return (perror("Failed to allocate memory for the map\n"), NULL);
	fd = open(MAP_FILE, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening the file\n"), NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
        len = ft_strlen_nl(line);
		map[i] = (char *)malloc(sizeof(char) * (len + 1));
        if (map[i] == NULL)
			return (perror("Failed to allocated memory for line\n"), NULL);
        ft_strlcpy(map[i], line, len + 1);
        free(line);
        i++;
	}
    close(fd);
    return (map);
}

char	**read_map(t_data *data)
{
	// int		count;
	char	**map;

	// char *line;
    
	// FIRST PASS - Comptage de line pour ensuite malloc la map
	data->game->rows = 0;
	ft_count_map_lines(data);
	ft_printf("game rows -> %d\n", data->game->rows);
    
	// SECOND PASS - Lire dans la map
	map = fill_map(data->game->rows);
	if (map == NULL)
		return (NULL);
	
    // check Legal caracters (0 1 C E P)
	if (!(check_caracters(map, data)))
	{
		ft_printf("Maps must only contain these 5 caracters : [0 - 1 - C - P - E]\n");
		return (NULL);
	}
	// Minimum requis At least one C and only one E & P
	if (!(get_map_info(map, data)))
		return (NULL);
	// Is rectangular ??
	if (!(is_rectangular(map, data)))
		return (NULL);
	// Walls surrounded ??
	if (!(surrounded_by_walls(map, data)))
		return (NULL);
	// Is map valid ? Flood Fill
	if (!(is_map_valid(map, data)))
		return (NULL);
	return (map);
}
/* We read the map once to get the number of lines 
	We malloc and store the map with the fill_map function 
	*/

int	ber_extension(const char *filename)
{
	int flag;
	const char *dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	flag = ft_strncmp(dot, ".ber", 4);
	if (flag == 0)
		return (ft_printf("GOOD EXTENSION FOR MAP\n"), 1);
	return (0);
}