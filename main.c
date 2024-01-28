/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:41 by mbest             #+#    #+#             */
/*   Updated: 2024/01/28 21:31:38 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	t_data		data;
	// t_game		game;
	int rows;
	char **map;

	if (!(ber_extension(MAP_FILE)))
		return (ft_printf("Invalid map. Must have a .ber extension.\n"), 1);
	fill_data_struct(&data);
	rows = 0;
	map = read_map(&data);
    if (map == NULL)
		return (1);
	printf("Printing out the map\n");
	printf("Rows = %d\n", data.game->rows);
    for (int i = 0; i < data.game->rows; i++)
    {
        ft_printf("%s\n", map[i]);
    }
	// ALL CHECKS DONE 
	
	fill_game_struct(&data, map);
	printf("Number of rows =\t%d\n", data.game->rows);
	printf("Number of Moves =\t%d\n", data.game->moves);
	printf("Number of collected =\t%d\n", data.game->collected);
	printf("Number of Collectibles =\t%d\n", data.game->nb_collectibles);
	printf("Player position x =\t%d\n", data.game->pos_x);
	printf("Player position y =\t%d\n", data.game->pos_y);
    for (int i = 0; i < rows; i++)
    {
        ft_printf("%s\n", data.game->map[i]);
    }
	
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "So Long :D");
	if (data.win_ptr == NULL)
		return (free(data.mlx_ptr), 1);
	// data.img_ptr = mlx_xpm_file_to_image(data.mlx_ptr, "assets/player/coin_1.xpm", &x, &y);
	if(!(ft_init_player(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	if (!(ft_init_tiles(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	if (!(ft_init_walls(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	if (!(ft_init_exit(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	if (!(ft_init_collectibles(&data)))
		return (free(data.win_ptr), free(data.mlx_ptr), 1);
	initialize_map(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);

	mlx_loop(data.mlx_ptr);

	return (0);
}
