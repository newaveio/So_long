/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:37:26 by mbest             #+#    #+#             */
/*   Updated: 2023/12/06 18:42:40 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    open_map()
{
    int fd;
    int nbr_of_lines;
    int end_of_file;
    char *temp;
    char *filename = "map.txt";
    
    end_of_file = 0;
    nbr_of_lines = 0;
    fd = open(filename, O_RDONLY);
    while(end_of_file == 0)
    {
        temp = get_next_line(fd);
        if (temp == NULL)
            end_of_file = 1;
        else
            nbr_of_lines++;
    }
    ft_printf("Number of lines: %d\n", nbr_of_lines);
}

int main(void)
{
    open_map();
    return (0);
}