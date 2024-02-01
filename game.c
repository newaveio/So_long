/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:35 by mbest             #+#    #+#             */
/*   Updated: 2024/02/01 18:51:44 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	player_move(t_data *data, int a)
{
	int flag;

	data->game->old_x = data->game->pos_x;
	data->game->old_y = data->game->pos_y;
	if (a == 1 || a == 3)
		flag = -1;
	else
		flag = 1;
	data->game->map[data->game->pos_y][data->game->pos_x] = '0';
	if (a == 3 || a == 4)
	{
		if (data->game->map[data->game->pos_y][data->game->pos_x+flag] == 'C')
		{
			collect(data, flag);
			data->game->collected++;
		}
		if (data->game->map[data->game->pos_y][data->game->pos_x+flag] == 'X')
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		if (data->game->map[data->game->pos_y][data->game->pos_x+flag] == 'E' && data->game->collected == data->game->nb_collectibles)
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		data->game->map[data->game->pos_y][data->game->pos_x+flag] = 'P';
		data->game->pos_x += flag;
		data->game->moves++;
	}
	else
	{
		if (data->game->map[data->game->pos_y+flag][data->game->pos_x] == 'C')
		{
			collect(data, flag);
			data->game->collected++;
		}
		if (data->game->map[data->game->pos_y+flag][data->game->pos_x] == 'X')
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		if (data->game->map[data->game->pos_y+flag][data->game->pos_x] == 'E' && data->game->collected == data->game->nb_collectibles)
		{
			data->game->moves++;
			ft_printf("Number of moves = %d\n", data->game->moves);
			on_destroy(data);
		}
		data->game->map[data->game->pos_y+flag][data->game->pos_x] = 'P';
		data->game->pos_y += flag;
		data->game->moves++;
	}
	print_map(data);
}

void	collect(t_data *data, int flag)
{
	printf("ENTERED COLLECT FUNCTION\n\n");
	int i;

	i = 0;
	while (i < data->game->nb_collectibles)
	{
		if ((data->collectibles[i].x == data->game->pos_x+flag && data->collectibles[i].y == data->game->pos_y) || (data->collectibles[i].x == data->game->pos_x && data->collectibles[i].y == data->game->pos_y+flag))
		{
			*(data->collectibles[i].collected) = 1;
			printf("123456789\ncol.x = %d\tcol.y = %d\tcol.collected = %d\n", data->collectibles[i].x, data->collectibles[i].y, *(data->collectibles[i].collected));
			printf("pos x = %d\tpos y = %d\n\n", data->game->pos_x, data->game->pos_y+flag);
			break ;
		}
		printf("col.x = %d\tcol.y = %d\tcol.collected = %d\n", data->collectibles[i].x, data->collectibles[i].y, *(data->collectibles[i].collected));
		printf("pos x = %d\tpos y = %d\n\n", data->game->pos_x, data->game->pos_y+flag);
		i++;
	}
	// for (int k = 0; k < data->game->nb_collectibles; k++)
	// 	printf("collectible[%d] --- x = %d\ty = %d\tcollected = %d\n", k, data->collectibles[k].x, data->collectibles[k].y, *(data->collectibles[k].collected));
}

int		mvt_checker(t_data *data, int a)
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
	if (a == 3 || a == 4)
	{
		if (data->game->map[y][x+flag] != '1' && data->game->map[y][x+flag] != 'E')
			return (1);
		if (data->game->map[y][x+flag] == 'E' && data->game->collected == data->game->nb_collectibles)
			return (1);
		else
			return (print_map(data), 0);
	}
	else
	{
		if (data->game->map[y+flag][x] != '1' && data->game->map[y+flag][x] != 'E')
			return (1);
		if (data->game->map[y+flag][x] == 'E' && data->game->collected == data->game->nb_collectibles)
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
		data->player_dir =
		if(is_mvt_possible(data, "up"))
		{
			data->player_is_moving = 1;
			player_move(data, 1);
			data->player_is_moving = 0;
		}
	}
	else
	{
		if (is_mvt_possible(data, "down"))
		{
			data->player_is_moving = 1;
			player_move(data, 2);
			data->player_is_moving = 0;
		}
	}
}

void	mvt_lr(t_data *data, int keysym)
{
	if (keysym == 65361)
	{
		if (is_mvt_possible(data, "left"))
		{
			data->player_is_moving = 1;
			player_move(data, 3);
			data->player_is_moving = 0;
		}
	}
	else
	{
		if (is_mvt_possible(data, "right"))
		{
			data->player_is_moving = 1;
			player_move(data, 4);
			data->player_is_moving = 0;
		}
	}
}

void	initialize_map(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (y < data->game->rows)
	{
		x = 0;
		while (x < data->game->cols)
		{
			if (data->game->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tile_text[0], x * TILE_SIZE, y * TILE_SIZE);
			if (data->game->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_text[0], x * TILE_SIZE, y * TILE_SIZE);
			if (data->game->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall_text[0], x * TILE_SIZE, y * TILE_SIZE);
			if (data->game->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_text[0], x * TILE_SIZE, y * TILE_SIZE);
			// if (data->game->map[y][x] == 'C')
			// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collec_text[0], x * TILE_SIZE, y * TILE_SIZE);
			// if (data->game->map[y][x] == 'X')
			// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->opps_text[0], x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	draw_moves(t_data *data)
{
	char *moves;
	char *str_moves;
	char *buffer;

	moves = ft_strdup("MOVES");
	str_moves = ft_itoa(data->game->moves);
	if (data->game->moves != 0)
	{
		buffer = ft_itoa(data->game->moves - 1);
		mlx_string_put(data->mlx_ptr, data->win_ptr, TILE_SIZE * 2.5, data->window->height + (EXTRA_HEIGHT * .5), 0x000000, buffer);
		free(buffer);
	}
	mlx_string_put(data->mlx_ptr, data->win_ptr, TILE_SIZE, data->window->height + (EXTRA_HEIGHT * .5), 0xFFFFFF, moves);
	mlx_string_put(data->mlx_ptr, data->win_ptr, TILE_SIZE * 2.5, data->window->height + (EXTRA_HEIGHT * .5), 0xFFFFFF, str_moves);
	free(str_moves);
	free(moves);
}

void	ft_update_map(t_data *data, int old_x, int old_y)
{
	if (old_x != 0 || old_x != 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tile_text[0], old_x * TILE_SIZE, old_y * TILE_SIZE); // tiles
	data->img_to_win = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_text[0], (data->game->pos_x) * TILE_SIZE, (data->game->pos_y) * 32); // player
	draw_moves(data);
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
	ft_update_map(data, data->game->old_x, data->game->old_y);
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
	data->window = (t_window *)malloc(sizeof(t_window));
}

void    fill_game_struct(t_data *data, char **map)
{
	int i;
	int j;
	(void)map;
	
	i = 0;
	j = 0;
    data->game->collected = 0;
	data->game->cols = ft_strlen_nl(map[0]);
    data->game->moves = 0;
	data->window->width = data->game->cols * TILE_SIZE;
	data->window->height = data->game->rows * TILE_SIZE;
}

void anim_opps(t_data *data, int frame)
{
	int i;

	i = 0;
	while (i < data->game->nb_x)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->opps_text[frame], data->enemies[i].x * TILE_SIZE, data->enemies[i].y * TILE_SIZE);
		i++;
	}
}
void	anim_exit(t_data *data, int frame)
{
	if (data->game->collected == data->game->nb_collectibles)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_text[frame], data->game->exit_x * TILE_SIZE, data->game->exit_y * TILE_SIZE);
}

void	anim_collectibles(t_data *data, int frame)
{
	int i;

	i = 0;
	while (i < data->game->nb_collectibles)
	{
		// printf("data->collectibles[%d] = %d\n", i, *(data->collectibles[i].collected));
		if (*(data->collectibles[i].collected) == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collec_text[frame], data->collectibles[i].x * TILE_SIZE, data->collectibles[i].y * TILE_SIZE);
		i++;
	}	
}

void	anim_player(t_data *data, int frame)
{
	
}

int	animation_update(void *param)
{
	int opps_frame;
	int exit_frame;
	int col_frame;
	int player_frame;

	t_data *data = (t_data *)param;
	opps_frame = (data->anim_counter[0]++ / 2000) % 4;
	exit_frame = (data->anim_counter[1]++ / 4000) % 4 + 1;
	col_frame = (data->anim_counter[2]++ / 2000) % 4;
	player_frame = (data->anim_counter[3]++ / 500) % 8;
	anim_opps(data, opps_frame);
	anim_exit(data, exit_frame);
	anim_collectibles(data, col_frame);
	anim_player(data, player_frame);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_text[0], data->game->pos_x * TILE_SIZE, data->game->pos_y * TILE_SIZE);
	return (0);
}

// int	animation_update(void *param)
// {
// 	int i;

// 	i = 0;
// 	t_data *data = (t_data *)param;
// 	data->anim_counter[0]++;
// 	int current_frame = (data->anim_counter[0] / 2) % 4;
// 	while (i < data->game->nb_x)
// 	{
// 		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->opps_text[current_frame], data->enemies[i].x * TILE_SIZE, data->enemies[i].y * TILE_SIZE);
// 		i++;
// 	}
// 	return (0);
// }


/*
int event_loop(void *param)
{
    t_data *data = (t_data *)param;

    // Update game state
    update_collectibles(data);
    update_enemies(data);

    // Render game state
    collectibles(data);
    enemies(data);

    return (0);
}

mlx_loop_hook(data.mlx_ptr, event_loop, &data);

FIX THE BUG OF RACE CONDITION*/