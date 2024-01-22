/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:41 by mbest             #+#    #+#             */
/*   Updated: 2024/01/22 19:29:18 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/headers/ft_printf.h"
#include "libft/headers/libft.h"

int	ft_count_map_lines(int *count)
{
	int		fd;
	char	*line;

	fd = open("maps/map_1.ber", O_RDONLY);
	if (fd < 0)
		return (perror("Error opening the file\n"), 0); // Error occured (-1)
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		(*count)++;
	}
	close(fd);
	return (1);
}

char	**fill_map(int count)
{
	int		i;
	int		fd;
	int		len;
    char    *line;
	char	**map;

	map = (char **)malloc(count * sizeof(char *));
	if (map == NULL)
		return (perror("Failed to allocate memory for the map\n"), NULL);
	fd = open("maps/map_1.ber", O_RDONLY);
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

char	**read_map(int *rows)
{
	int		count;
	char	**map;

	// char *line;
    
	// FIRST PASS - Comptage de line pour ensuite malloc la map
	count = 0;
	ft_count_map_lines(&count);
	ft_printf("Count = %d\n", count);
	*rows = count;
    
	// SECOND PASS - Lire dans la map
	map = fill_map(count);
	if (map == NULL)
		return (NULL);
	
	// BASIC CHECK - Legal caracters (0 1 C E P) - At least one C and only one E & P - Rectangular - Walls
	printf("Number of rows = %d\n", count);
    // check_caracters(map, *rows);
	if (!(check_caracters(map, count)))
	{
		ft_printf("Maps must only contain these 5 caracters : [0 - 1 - C - P - E]\n");
		return (NULL);
	}
	// Minimum requis
	if (!(get_map_info(map, count)))
		return (NULL);
	// Is rectangular ??
	if (!(is_rectangular(map, count)))
		return (NULL);
	// Walls surrounded ??
	if (!(surrounded_by_walls(map, count)))
		return (NULL);
	// Is map valid ? Flood Fill
	if (!(is_map_valid(map, count)))
		return (NULL);
	return (map);
}
/* We read the map once to get the number of lines 
	We malloc and store the map with the fill_map function 
	*/
int	main(void)
{
	int rows;
	char **map;

	rows = 0;
	map = read_map(&rows);
    if (map == NULL)
		return (1);
	printf("Printing out the map\n");
	printf("Rows = %d\n", rows);
    for (int i = 0; i < rows; i++)
    {
        ft_printf("%s\n", map[i]);
    }
	return (1);
}