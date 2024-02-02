/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:08:07 by mbest             #+#    #+#             */
/*   Updated: 2024/02/02 17:51:25 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_init_player_bis(t_data *data)
{
	char *buf1;
	char *buf2;
	char *buf_itoa;
	char *file;

	buf_itoa = ft_itoa(data->misc1 + 1);
	buf1 = ft_strjoin("assets/player/mvt", buf_itoa);
	free(buf_itoa);
	buf2 = ft_strjoin(buf1, "/");
	free(buf1);
	buf_itoa = ft_itoa(data->misc2 + 1);
	buf1 = ft_strjoin(buf_itoa, ".xpm");
	file = ft_strjoin(buf2, buf1);
	return (free(buf1), free(buf2), free(buf_itoa), file);
}

int	ft_init_player(t_data *data)
{
	int x;
	int y;
	char *file;

	data->misc1 = -1;
	x = TILE_SIZE;
	y = TILE_SIZE;
	while (++data->misc1 < 4)
	{
		data->misc2 = -1;
		while (++data->misc2 < 8)
		{
			file = ft_init_player_bis(data);
			data->player_text[data->misc1][data->misc2] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
			if (data->player_text[data->misc1][data->misc2] == NULL)
				return (ft_printf("[TEXTURE] - Failed to load player[%d][%d]\n", data->misc1, data->misc2), 0);
			free(file);
		}
	}
	return (1);
}

int ft_load_textures(t_data *data)
{
	if(!(ft_init_player(data)))
		return (0);
	if (!(ft_init_tiles(data)))
		return (0);
	if (!(ft_init_walls(data)))
		return (0);
	if (!(ft_init_exit(data)))
		return (0);
	if (!(ft_init_collectibles(data)))
		return (0);
	if (!(ft_init_opps(data)))
		return (0);
	return (1);
}
