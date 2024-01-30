/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:42:58 by mbest             #+#    #+#             */
/*   Updated: 2024/01/30 22:06:02 by mbest            ###   ########.fr       */
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
	char	**map;
    
	data->game->rows = 0;
	ft_count_map_lines(data);
	map = fill_map(data->game->rows);
	if (map == NULL)
		return (NULL);
	if (!(check_caracters(map, data)))
	{
		ft_printf("Maps must only contain these 6 caracters : [0 - 1 - C - P - E - X]\n");
		return (NULL);
	}
	if (!(get_map_info(map, data)))
		return (NULL);
	if (!(is_rectangular(map, data)))
		return (NULL);
	if (!(surrounded_by_walls(map, data)))
		return (NULL);
	if (!(is_map_valid(map, data)))
		return (NULL);
	return (map);
}

int	ber_extension(const char *filename)
{
	int flag;
	const char *dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	flag = ft_strncmp(dot, ".ber", 4);
	if (flag == 0)
		return (1);
	return (0);
}