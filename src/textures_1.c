/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:07:03 by mbest             #+#    #+#             */
/*   Updated: 2024/02/19 10:42:04 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	ft_init_opps(t_data *data)
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
		file = ft_itoa(i+1);
		buf = ft_strjoin("assets/opps/op2/op_", file);
		free(file);
		file = ft_strjoin(buf, ".xpm");
		data->opps_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
		// mlx_get_data_addr(data->opps_text[i], &data->bpp, &data->size_line, &data->endian);
		if (data->opps_text[i] == NULL)
			return (ft_printf("[TEXTURES] - Failed to load opps [%d]\n", i+1), 0);
		(free(buf), free(file));
		i++;
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
	x = TILE_SIZE;
	y = TILE_SIZE;
	while (i < 5)
	{
		file = ft_itoa(i+1);
		buf = ft_strjoin("assets/exit/exit_", file);
		free(file);
		file = ft_strjoin(buf, ".xpm");
		data->exit_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
		if (data->exit_text[i] == NULL)
			return (ft_printf("[TEXTURE] - Failed to load exit\n"), 0);
		(free(buf), free(file));
		i++;
	}
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
		file = ft_itoa(i+1);
		buf = ft_strjoin("assets/collectible/col_", file);
		free(file);
		file = ft_strjoin(buf, ".xpm");
		data->collec_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
		if (data->collec_text[i] == NULL)
			return (ft_printf("[TEXTURE][%d] - Failed to load collectibles\n", i+1), 0);
		(free(buf), free(file));
		i++;
	}
	return (1);
}
