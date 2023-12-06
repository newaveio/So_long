#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void ft_putchar(char c, int *counter);
void ft_putstr(const char *str, int *counter);
int ft_intlen(int n);
int  ft_uintlen(unsigned int n);
char *ft_uitoa(unsigned int n);
void ft_putnbr_hex_cap(size_t n, int *counter);
void ft_putnbr_hex(size_t n, int *counter);
void ft_print_str(const char c, va_list args, int *counter);
void ft_print_num(const char c, va_list args, int *counter);
void ft_print_hex(const char c, va_list args, int *counter);
void ft_format(va_list args, const char c, int *counter);
int ft_printf(const char *format, ...);
char *ft_itoa(int n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);

#endif