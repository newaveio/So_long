/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:20:10 by mbest             #+#    #+#             */
/*   Updated: 2023/11/28 15:23:14 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_putnbr_hex(size_t n, int *counter)
{
    const char *hex_digits = "0123456789abcdef";

    if(n >= 16)
        ft_putnbr_hex(n / 16, counter);
    ft_putchar(hex_digits[n % 16], counter);
}

void ft_putnbr_hex_cap(size_t n, int *counter)
{
    const char *hex_digits = "0123456789ABCDEF";

    if(n >= 16)
        ft_putnbr_hex_cap(n / 16, counter);
    ft_putchar(hex_digits[n % 16], counter);
}

void ft_print_hex(const char c, va_list args, int *counter)
{
    if (c == 'x')
        ft_putnbr_hex(va_arg(args, int), counter);
    else
        ft_putnbr_hex_cap(va_arg(args, int), counter);
}

char *ft_uitoa(unsigned int n)
{
    int i;
    int len;
    char *res;

    // What should happen if n is larger than an unsigned int ???


    i = 0;
    len = ft_uintlen(n);
    res = (char *)malloc(sizeof(char) * (len + 1));
    if(!res)
        return(NULL);
    res[len] = '\0';
    while(len > i)
    {
        res[len-- - 1] = (n % 10) + '0';
        n /= 10;
    }
    return(res);
}

void ft_print_num(const char c, va_list args, int *counter)
{
    char *tmp;
    int n;
    unsigned int un;

    if (c == 'd' || c == 'i')
    {
        n = va_arg(args, int);
        tmp = ft_itoa(n);
        ft_putstr(tmp, counter);
    }
    else
    {
        un = va_arg(args, unsigned int);
        tmp = ft_uitoa(un);
        ft_putstr(tmp, counter);
    }
    free(tmp);
}
