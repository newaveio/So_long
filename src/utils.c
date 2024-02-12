/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:40:45 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 22:56:20 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_strlen_nl(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i] != '\n')
        i++;
    return (i);
}

int	ft_count_map_lines(t_data *data, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening the file\n"), 0);
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		(data->game->rows)++;
	}
	close(fd);
	return (1);
}

void	print_map(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->game->rows)
		ft_printf("%s\n", data->game->map[i]);
}
