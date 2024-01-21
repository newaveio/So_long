/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:41 by mbest             #+#    #+#             */
/*   Updated: 2024/01/21 19:50:03 by mbest            ###   ########.fr       */
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
	{
		perror("Failed to allocate memory for the map\n");
		return (NULL);
	}
	fd = open("maps/map_1.ber", O_RDONLY);
	if (fd < 0)
		return (perror("Error opening the file\n"), NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
        len = ft_strlen(line);
		map[i] = (char *)malloc(sizeof(char) * (len + 1));
        if (map[i] == NULL)
        {
			perror("Failed to allocated memory for line\n");
			return (NULL);
        }
        ft_strlcpy(map[i], line, len);
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
    
	// SECOND PASS - Lire dans la map
	map = fill_map(count);
	if (map == NULL)
		return (NULL);

    
	*rows = count;
	return (map);
}

int	main(void)
{
	int rows;
	char **map;

	rows = 0;
	map = read_map(&rows);
    
    for (int i = 0; i < rows; i++)
    {
        ft_printf("%s\n", map[i]);
    }
	return (1);
}