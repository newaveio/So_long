/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:35 by mbest             #+#    #+#             */
/*   Updated: 2024/01/25 20:04:31 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	player_move(t_data *data, int a)
{
	int x;
	int y;
	int flag;

	x = data->game->pos_x;
	y = data->game->pos_y;
	if (a == 1 || a == 3)
		flag = -1;
	else
		flag = 1;
	data->game->map[x][y] = '0';
	if (a == 1 || a == 2)
	{
		if (data->game->map[x+flag][y] == 'C')
			data->game->collected++;
		if (data->game->map[x+flag][y] == 'E' && data->game->collected == data->game->nb_collectibles)
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		data->game->map[x+flag][y] = 'P';
		data->game->pos_x += flag;
		data->game->moves++;
	}
	else
	{
		if (data->game->map[x][y+flag] == 'C')
			data->game->collected++;
		if (data->game->map[x][y+flag] == 'E' && data->game->collected == data->game->nb_collectibles)
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		data->game->map[x][y+flag] = 'P';
		data->game->pos_y += flag;
		data->game->moves++;
	}
	print_map(data);
}

int		mvt_checker(t_data *data, int a)
{
	int x; // remove and change structure to make it shorter ex: d->g->x
	int y; // remove and change structure to make it shorter ex: d->g->y
	int flag;

	x = data->game->pos_x; // remove and change structure to make it shorter ex: d->g->x
	y = data->game->pos_y; // remove and change structure to make it shorter ex: d->g->y
	if (a == 1 || a == 3)
		flag = -1;
	else
		flag = 1;
	if (a == 1 || a == 2)
	{
		if (data->game->map[x+flag][y] != '1' && data->game->map[x+flag][y] != 'E')
			return (1);
		if (data->game->map[x+flag][y] == 'E' && data->game->collected == data->game->nb_collectibles)
			return (1);
		else
			return (print_map(data), 0);
	}
	else
	{
		if (data->game->map[x][y+flag] != '1' && data->game->map[x][y+flag] != 'E')
			return (1);
		if (data->game->map[x][y+flag] == 'E' && data->game->collected == data->game->nb_collectibles)
			return (1);
		else
			return (print_map(data), 0);
	}
}
/* int a ----- 1 = up ---- 2 = down ---- 3 = left ---- 4 = right */

void	print_map(t_data *data)
{
	int i;

	i = 0;
	while (i < data->game->rows)
	{
		ft_printf("%s\n", data->game->map[i]);
		i++;
	}
}

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
		if(is_mvt_possible(data, "up"))
			player_move(data, 1);
	}
	else
	{
		if (is_mvt_possible(data, "down"))
			player_move(data, 2);
	}
}

void	mvt_lr(t_data *data, int keysym)
{
	if (keysym == 65361)
	{
		if (is_mvt_possible(data, "left"))
			player_move(data, 3);
	}
	else
	{
		if (is_mvt_possible(data, "right"))
			player_move(data, 4);
	}
}


int	on_keypress(int keysym, t_data *data)
{
	if (keysym == 65362 || keysym == 65364)
		mvt_ud(data, keysym);
	if (keysym == 65361 || keysym == 65363)
		mvt_lr(data, keysym);
	if (keysym == 65307)
		return (on_destroy(data));
	ft_printf("Collected\t%d/%d\n", data->game->collected, data->game->nb_collectibles);
	ft_printf("Number of moves = %d\n", data->game->moves);
	return (0);
}
/* 65362 up - 65364 down - 65361 left - 65363 right - 65307 esc */

int on_destroy(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}

void	fill_data_struct(t_data *data)
{
	data->game = (t_game *)malloc(sizeof(t_game));	
}

void    fill_game_struct(t_data *data, char **map, int rows)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
    data->game->collected = 0;
    data->game->moves = 0;
	data->game->nb_collectibles = 0;
	data->game->rows = rows;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				data->game->nb_collectibles++;
			if (map[i][j] == 'P')
			{
				data->game->pos_x = i;
				data->game->pos_y = j;
			}
			j++;
		}
		i++;
	}
    data->game->map = copy_map(map, rows);
}
