/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_text_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:07 by mbest             #+#    #+#             */
/*   Updated: 2024/03/13 16:10:26 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    free_col_text(t_data *data)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (data->collec_text[i] != NULL)
        {
            mlx_destroy_image(data->mlx_ptr, data->collec_text[i]);
        }
        i++;
    }
}

void    free_opps_text(t_data *data)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (data->opps_text[i] != NULL)
        {
            mlx_destroy_image(data->mlx_ptr, data->opps_text[i]);
        }
        i++;
    }
}
