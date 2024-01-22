/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:40:45 by mbest             #+#    #+#             */
/*   Updated: 2024/01/22 15:45:06 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/headers/ft_printf.h"
#include "libft/headers/libft.h"

int ft_strlen_nl(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i] != '\n')
        i++;
    return (i);
}