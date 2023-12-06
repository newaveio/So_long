/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:12:35 by mbest             #+#    #+#             */
/*   Updated: 2023/11/28 16:27:00 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// // in libft
// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
// // in libft
// char	*ft_strdup(const char *s)
// {
// 	char	*str;
// 	int		i;

// 	i = ft_strlen(s);
// 	str = (char *)malloc(sizeof(char) * (i + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }


// // in libft
// char *ft_itoa(int n)
// {
//     int i;
//     int len;
//     char *res;

//     if (n == -2147483648)
//         return(ft_strdup("-2147483648"));
//     i = 0;
//     len = ft_intlen(n);
//     res = (char *)malloc(sizeof(char) * (len + 1));
//     if(!res)
//         return(NULL);
//     if(n < 0)
//     {
//         res[0] = '-';
//         n *= -1;
//         i++;
//     }
//     res[len] = '\0';
//     while(len > i)
//     {
//         res[len-- - 1] = (n % 10) + '0';
//         n /= 10;
//     }
//     return(res);
// }

void ft_print_str(const char c, va_list args, int *counter)
{
    if (c == 's')
    {
        const char *str;
        str = va_arg(args, const char *);
        if (str == NULL)
            ft_putstr("(null)", counter);
        else
            ft_putstr(str, counter);
    }
    else
    {
        const void *ptr;
        ptr = va_arg(args, const void *);
        if (ptr == NULL)
            ft_putstr("(nil)", counter);
        else
        {
            ft_putstr("0x", counter);
            ft_putnbr_hex((size_t)ptr, counter);
        }
    }
}

void ft_format(va_list args, const char c, int *counter)
{
    if (c == '%')
        ft_putchar('%', counter);
    else if (c == 'c')
        ft_putchar((char)va_arg(args, int), counter);
    else if (c == 's' || c == 'p')
        ft_print_str(c, args, counter);
    else if (c == 'd' || c == 'i' || c == 'u')
        ft_print_num(c, args, counter);
    else if (c == 'x' || c == 'X')
        ft_print_hex(c, args, counter);
    else
        return ;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    size_t len;
    size_t i;
    int counter;

    len = ft_strlen(format);
    i = 0;
    counter = 0;
    while(i < len)
    {
        if(format[i] == '%' )
        {
            i++;
            ft_format(args, format[i], &counter);
        }
        else
            ft_putchar(format[i], &counter);
        i++;
    }
    va_end(args);
    return (counter);
}

// int main(void)
// {
//     void *ptr = "Hello la mif";
//     int j = ft_printf("Output:\t\t%p %c %i %u\n", ptr, 'c', -2147483649, 42949672950);
//     int i = printf("Output:\t\t%p %c %i %u\n", ptr, 'c', (int)-2147483649, (unsigned int)42949672950);
//     // int i = printf("Output:\t\t%p %c %i %u %% Hello\n", ptr, 'c', (int)-2147483649, (unsigned int)42949672950);
//     // int i = printf("Output:\t\t%p %c %i %u % Hello\n", ptr, 'c', (int)-2147483649, (unsigned int)42949672950);
//     // int i = printf("Output:\t\t%p %c %i %u % Hello\n", ptr, 'c', (int)-2147483649, (unsigned int)42949672950);


//     printf("i = %d\n", i);
//     printf("j = %d\n", j);
//     // ft_printf("\n[ft_printf]\tOutput:\t\t%x %X %% %s\n", 1000, 1000, "Salut la mif");
//     // printf("[printf]\tOutput:\t\t%x %X %% %s\n", 1000, 1000, "Salut la mif");

//     // ft_printf("\n[ft_printf]\tOutput:\t\t%d %d %d %x %X\n", INT_MAX, 0);
//     // printf("[printf]\tOutput:\t\t%d %d %d %x %X\n", INT_MAX, 0);

//     return(0);
// }