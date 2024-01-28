/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:41 by mbest             #+#    #+#             */
/*   Updated: 2024/01/28 23:26:14 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int i;
	char **map;
	t_data		data;

	if (!(ber_extension(MAP_FILE)))
		return (ft_printf("Invalid map. Must have a .ber extension.\n"), 1);
	fill_data_struct(&data);
	map = read_map(&data);
    if (map == NULL)
		return (1);
	fill_game_struct(&data, map);
	i = 0;
	while(i < data.game->rows)
		ft_printf("%s\n", data.game->map[i++]);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	int window_w = data.game->cols * TILE_SIZE; // add in structure
	int window_h = data.game->rows * TILE_SIZE; // add in structure
	data.win_ptr = mlx_new_window(data.mlx_ptr, window_w, window_h + 200, "So Long :D");
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), 1);
	if (!(ft_load_textures(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	initialize_map(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

// int	main(void)
// {
// 	int i;
// 	char **map;
// 	t_data		data;

// 	if (!(ber_extension(MAP_FILE)))
// 		return (ft_printf("Invalid map. Must have a .ber extension.\n"), 1);
// 	fill_data_struct(&data);
// 	map = read_map(&data);
//     if (map == NULL)
// 		return (1);
// 	fill_game_struct(&data, map);
// 	i = 0;
// 	while(i < data.game->rows)
// 		ft_printf("%s\n", data.game->map[i++]);
// 	data.mlx_ptr = mlx_init();
// 	if (data.mlx_ptr == NULL)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "So Long :D");
// 	if (data.win_ptr == NULL)
// 		return (free(data.mlx_ptr), 1);
// 	if (!(ft_load_textures(&data)))
// 		return (free(data.win_ptr), free(data.mlx_ptr), 1);
// 	initialize_map(&data);
// 	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
// 	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
// 	mlx_loop(data.mlx_ptr);
// 	return (0);
// }
