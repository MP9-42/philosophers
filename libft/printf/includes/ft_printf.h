/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:40:04 by MP9               #+#    #+#             */
/*   Updated: 2025/10/02 19:55:55 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# if defined(__linux__)
#  define NULL_STRING "(nil)"
#  define NULL_STRING_LENGTH 5
# elif defined(__APPLE__)
#  define NULL_STRING "0x0"
#  define NULL_STRING_LENGTH 3
# else
#  error "Unsupported platform"
# endif

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

int		ft_printf(const char *f, ...);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
size_t	ft_strlen(const char *s);

int		ft_putnbr_hex(unsigned long n, int uppercase);
int		ft_putfloat(double n, int precision);
int		ft_printf(const char *f, ...);
int		count_digits(int n);
int		count_digits_unsigned(unsigned int n);
int		ft_putnbr_unsigned(unsigned int n);

#endif
