/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:38:09 by mbest             #+#    #+#             */
/*   Updated: 2024/02/12 22:38:34 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		is_mvt_possible(t_data *data, char *mvt)
{
	if (ft_strncmp(mvt, "up", 2) == 0)
		return (mvt_checker(data, 1));
	else if (ft_strncmp(mvt, "down", 4) == 0)
		return (mvt_checker(data, 2));
	else if (ft_strncmp(mvt, "left", 4) == 0)
		return (mvt_checker(data, 3));
	else if (ft_strncmp(mvt, "right", 5) == 0)
		return (mvt_checker(data, 4));
	else
		return (0);
}

void	mvt_ud(t_data *data, int keysym)
{
	if (keysym == 65362)
	{
		data->player_dir = 0;
		if(is_mvt_possible(data, "up"))
		{
			data->player_is_moving = 1;
			player_move(data, 1);
		}
	}
	else
	{
		data->player_dir = 1;
		if (is_mvt_possible(data, "down"))
		{
			data->player_is_moving = 1;
			player_move(data, 2);
		}
	}
}

void	mvt_lr(t_data *data, int keysym)
{
	if (keysym == 65361)
	{
		data->player_dir = 2;
		if (is_mvt_possible(data, "left"))
		{
			data->player_is_moving = 1;
			player_move(data, 3);
		}
	}
	else
	{
		data->player_dir = 3;
		if (is_mvt_possible(data, "right"))
		{
			data->player_is_moving = 1;
			player_move(data, 4);
		}
	}
}
