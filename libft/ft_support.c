/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_support.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:11:53 by mbest             #+#    #+#             */
/*   Updated: 2023/11/28 15:23:00 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_putchar(char c, int *counter)
{
    (*counter)++;
    write(1, &c, 1);
}

void ft_putstr(const char *str, int *counter)
{
    int i;

    i = 0;
    while(str[i])
        ft_putchar(str[i++], counter);
}

int ft_intlen(int n)
{
    int len;

    len = 1;
    if(n < 0)
        len++;
    while(n / 10)
    {
        len++;
        n /= 10;
    }
    return(len);
}

int  ft_uintlen(unsigned int n)
{
    int len = 1;
    while(n / 10)
    {
        len++;
        n /= 10;
    }
    return(len);
}
