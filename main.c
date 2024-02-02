/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:41 by mbest             #+#    #+#             */
/*   Updated: 2024/02/02 18:08:25 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_map(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->game->rows)
	{
		free(data->game->map[i]);
		i++;
	}
	free(data->game->map);
}

void	free_structure(t_data *data)
{
	free_map(data);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc == 2)
	{
		if (!(check_map(&data, argv[1])))
			return (ft_printf("Invalid map.\n"), 1);
		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			return (ft_printf("Failled to init mlx_ptr\n"), 1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, data.window->width, data.window->height + EXTRA_HEIGHT, "So Long :D"); // make it general
		if (data.win_ptr == NULL)
			return (ft_printf("Failed to init win_ptr\n"), free(data.mlx_ptr), 1);
		if (!(ft_load_textures(&data)))
			return (free(data.win_ptr), free(data.mlx_ptr), 1);
		initialize_map(&data);
		mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
		mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
		mlx_loop_hook(data.mlx_ptr, animation_update, &data);
		mlx_loop(data.mlx_ptr);
		free_structure(&data);
	}
	else
		ft_printf("\nOops.. You need 2 arguments\n<./program_name> <map.ber>\n\n");
	return (0);
	}
