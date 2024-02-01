/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:07:03 by mbest             #+#    #+#             */
/*   Updated: 2024/02/01 21:51:37 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	ft_init_player(t_data *data)
// {
// 	int x;
// 	int y;

// 	x = 32;
// 	y = 32;
// 	data->player_text[0][0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/player/mvt1/1.xpm", &x, &y);
// 	if (data->player_text[0][0] == NULL)
// 		return (ft_printf("[TEXTURE] - Failed to load player\n"), 0);
// 	return (1);
// }

int	ft_init_player(t_data *data)
{
	int x;
	int y;
	char *buf1;
	char *buf2;
	char *file;

	data->misc1 = -1;
	x = 32;
	y = 32;
	while (++data->misc1 < 4)
	{
		data->misc2 = -1;
		while (++data->misc2 < 8)
		{
			buf1 = ft_strjoin("assets/player/mvt", ft_itoa(data->misc1+1));
			buf2 = ft_strjoin(buf1, "/");
			free(buf1);
			buf1 = ft_strjoin(ft_itoa(data->misc2+1), ".xpm");
			file = ft_strjoin(buf2, buf1);
			// printf("%s\n", file);
			data->player_text[data->misc1][data->misc2] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
			if (data->player_text[data->misc1][data->misc2] == NULL)
				return (ft_printf("[TEXTURE] - Failed to load player\n"), 0);
			printf("d->player[%d][%d] = %s\n", data->misc1, data->misc2, file);
			(free(buf1),free(buf2),free(file));
		}
	}
	return (1);
}

int	ft_init_exit(t_data *data)
{
	int i;
	int x;
	int y;
	char *buf;
	char *file;

	i = 0;
	x = 32;
	y = 32;
	while (i < 5)
	{
		buf = ft_strjoin("assets/exit/exit_", ft_itoa(i+1));
		file = ft_strjoin(buf, ".xpm");
		data->exit_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
		if (data->exit_text[i] == NULL)
			return (ft_printf("[TEXTURE] - Failed to load exit\n"), 0);
		i++;
	}
	return (1);
}

int	ft_init_tiles(t_data *data)
{
	int x;
	int y;

	x = TILE_SIZE;
	y = TILE_SIZE;
	data->tile_text[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/tiles/tile_3.xpm", &x, &y);
	if (data->tile_text[0] == NULL)
		return (ft_printf("[TEXTURE] - Failed to load tiles\n"), 0);
	return (1);
}

int	ft_init_walls(t_data *data)
{
	int x;
	int y;

	x = TILE_SIZE;
	y = TILE_SIZE;
	data->wall_text[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/wall/wall_2.xpm", &x, &y);
	if (data->wall_text[0] == NULL)
		return (ft_printf("[TEXTURE] - Failed to load walls\n"), 0);
	return (1);
}

int	ft_init_collectibles(t_data *data)
{
	int i;
	int x;
	int y;
	char *buf;
	char *file;
	
	i = 0;
	x = TILE_SIZE;
	y = TILE_SIZE;
	while (i < 4)
	{
		buf = ft_strjoin("assets/collectible/col_", ft_itoa(i+1));
		file = ft_strjoin(buf, ".xpm");
		data->collec_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
		if (data->collec_text[i] == NULL)
			return (ft_printf("[TEXTURE][%d] - Failed to load collectibles\n", i+1), 0);
		i++;
	}
	return (1);
}
