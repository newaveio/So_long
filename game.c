/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:35 by mbest             #+#    #+#             */
/*   Updated: 2024/01/30 23:56:33 by mbest            ###   ########.fr       */
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
			data->game->collected++;
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
			data->game->collected++;
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
			if (data->game->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collec_text[0], x * TILE_SIZE, y * TILE_SIZE);
			if (data->game->map[y][x] == 'X')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->opps_text[0], x * TILE_SIZE, y * TILE_SIZE);
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

int	ft_init_player(t_data *data)
{
	int x;
	int y;

	x = 32;
	y = 32;
	data->player_text[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/player/coin_1.xpm", &x, &y);
	if (data->player_text[0] == NULL)
		return (ft_printf("[TEXTURE] - Failed to load player\n"), 0);
	return (1);
}

int	ft_init_tiles(t_data *data)
{
	int x;
	int y;

	x = 32;
	y = 32;
	data->tile_text[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/tiles/tile_3.xpm", &x, &y);
	if (data->tile_text[0] == NULL)
		return (ft_printf("[TEXTURE] - Failed to load tiles\n"), 0);
	return (1);
}

int	ft_init_walls(t_data *data)
{
	int x;
	int y;

	x = 32;
	y = 32;
	data->wall_text[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/wall/wall_2.xpm", &x, &y);
	if (data->wall_text[0] == NULL)
		return (ft_printf("[TEXTURE] - Failed to load walls\n"), 0);
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
		data->exit_text[i] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/exit/exit_2.xpm", &x, &y);
		if (data->exit_text[i] == NULL)
			return (ft_printf("[TEXTURE] - Failed to load exit\n"), 0);
		i++;
	}
	return (1);
}

int	ft_init_collectibles(t_data *data)
{
	int x;
	int y;
	
	x = 32;
	y = 32;
	data->collec_text[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/collectible/col_1.xpm", &x, &y);
	if (data->collec_text[0] == NULL)
		return (ft_printf("[TEXTURE] - Failed to load collectibles\n"), 0);
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
	x = 32;
	y = 32;
	while (i < 4)
	{
		buf = ft_strjoin("assets/opps/op1/op1_", ft_itoa(i+1));
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

int	animation_update(void *param)
{
	int i;

	i = 0;
	t_data *data = (t_data *)param;
	data->anim_counter++;
	int current_frame = (data->anim_counter / 2) % 4;
	while (i < data->game->nb_x)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->opps_text[current_frame], data->enemies[i].x * TILE_SIZE, data->enemies[i].y * TILE_SIZE);
		i++;
	}
	return (0);
}
