/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_text_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:46:01 by mbest             #+#    #+#             */
/*   Updated: 2024/03/13 16:10:15 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_textures(t_data *data)
{
    free_player_text(data);
    free_tile_text(data);
    free_wall_text(data);
    free_exit_text(data);
    free_col_text(data);
    free_opps_text(data);
}

void	free_player_text(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 8)
		{
			if (data->player_text[i][j] != NULL)
			{
				mlx_destroy_image(data->mlx_ptr, data->player_text[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	free_tile_text(t_data *data)
{
    if (data->tile_text[0] != NULL)
    {
        mlx_destroy_image(data->mlx_ptr, data->tile_text[0]);
    }
}

void    free_wall_text(t_data *data)
{
    if (data->wall_text[0] != NULL)
    {
        mlx_destroy_image(data->mlx_ptr, data->wall_text[0]);
    }
}

void    free_exit_text(t_data *data)
{
    int i;

    i = 4;
    while (i < 5)
    {
        if (data->exit_text[i] != NULL)
        {
            mlx_destroy_image(data->mlx_ptr, data->exit_text[i]);
        }
        i++;
    }
}
