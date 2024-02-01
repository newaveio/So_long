/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:41 by mbest             #+#    #+#             */
/*   Updated: 2024/01/31 13:50:36 by mbest            ###   ########.fr       */
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
		printf("OKOKOK1\n");
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
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.window->width, data.window->height + EXTRA_HEIGHT, "So Long :D"); // make it general
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), 1);
	if (!(ft_load_textures(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	initialize_map(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop_hook(data.mlx_ptr, animation_update, &data);
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
