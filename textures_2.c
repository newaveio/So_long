/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:08:07 by mbest             #+#    #+#             */
/*   Updated: 2024/02/01 21:51:54 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		buf = ft_strjoin("assets/opps/op2/op_", ft_itoa(i+1));
		file = ft_strjoin(buf, ".xpm");
		data->opps_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, file, &x, &y);
		if (data->opps_text[i] == NULL)
			return (ft_printf("[TEX	data->enemies = (t_enemies *)malloc()TURE] - Failed to load opps (%d)\n", i+1), 0);
		i++;
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
