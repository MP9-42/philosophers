/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:39:55 by MP9               #+#    #+#             */
/*   Updated: 2025/10/02 19:37:13 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	convert_pointer(void *ptr)
{
	unsigned long	addr;
	int				count;

	addr = (unsigned long)ptr;
	count = 0;
	if (!ptr)
	{
		if (write(1, NULL_STRING, NULL_STRING_LENGTH) == -1)
			return (-1);
		return (NULL_STRING_LENGTH);
	}
	count += ft_putstr("0x");
	if (count == -1)
		return (-1);
	count += ft_putnbr_hex(addr, 0);
	return (count);
}

static int	format_specifier(const char *f, int i, va_list args)
{
	char	c;

	c = f[i];
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 0));
	if (c == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 1));
	if (c == 'p')
		return (convert_pointer(va_arg(args, void *)));
	if (c == '%')
		return (ft_putchar('%'));
	if (c == 'f')
		return (ft_putfloat(va_arg(args, double), 6));
	return (0);
}

int	ft_printf(const char *f, ...)
{
	va_list	args;
	int		count;
	int		prot;

	count = 0;
	va_start(args, f);
	while (*f)
	{
		if (*f == '%')
		{
			f++;
			prot = format_specifier(f, 0, args);
			if (prot == -1)
				return (-1);
		}
		else if (write(1, f, 1) == -1)
			return (-1);
		else
			prot = 1;
		count += prot;
		f++;
	}
	va_end(args);
	return (count);
}
