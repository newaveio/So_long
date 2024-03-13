/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:55:10 by mbest             #+#    #+#             */
/*   Updated: 2024/03/13 15:33:43 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int check_map(t_data *data, const char *filename)
{
	if (!(ber_extension(filename)))
		return (ft_printf("Must have a .ber extension.\n"), 0);
	if (!(fill_data_struct(data)))
		return (0);
	if (!(ft_count_map_lines(data, filename)))
		return (0);
	if (!(fill_map(data, filename)))
		return (0);
	if (!(read_map(data)))
		return (0);
	fill_game_struct(data);
	print_map(data);
	init_anim_counter(data);
	return (1);
}

int fill_map(t_data *data, const char *filename)
{
	int		i;
	int		fd;
	int		len;
    char    *line;

	data->buf_map = (char **)ft_calloc(data->game->rows, sizeof(char *));
	if (data->buf_map == NULL)
		return (ft_printf("Failed to allocate memory for the buffer map\n"), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error opening the file\n"), 0);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
        len = ft_strlen_nl(line);
		data->buf_map[i] = (char *)ft_calloc(len + 1, sizeof(char));
        if (data->buf_map[i] == NULL)
			return (ft_printf("Failed to allocated memory for line of buf_map\n"), 0);
        ft_strlcpy(data->buf_map[i], line, len + 1);
        free(line);
        i++;
	}
    close(fd);
    return (1);
}

int read_map(t_data *data)
{
	if (!(check_caracters(data)))
		return (0);
	if (!(get_map_info(data)))
		return (0);
	if (!(is_rectangular(data)))
		return (0);
	if (!(surrounded_by_walls(data)))
		return (0);
	if (!(is_map_valid(data)))
		return (0);
	return (1);
}
