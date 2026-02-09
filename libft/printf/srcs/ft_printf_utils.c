/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:39:44 by MP9               #+#    #+#             */
/*   Updated: 2025/08/29 20:37:59 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count = 1;
		if (n == INT_MIN)
			return (11);
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	count_digits_unsigned(unsigned int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int		count;
	int		temp;
	char	digit;

	count = 0;
	if (n >= 10)
	{
		temp = ft_putnbr_unsigned(n / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	digit = '0' + n % 10;
	if (write(1, &digit, 1) == -1)
		return (-1);
	return (count + 1);
}

static char	digit_to_hex(int digit, int uppercase)
{
	if (digit < 10)
		return ('0' + digit);
	else if (uppercase)
		return ('A' + digit - 10);
	else
		return ('a' + digit - 10);
}

int	ft_putnbr_hex(unsigned long n, int uppercase)
{
	int		count;
	int		tmp;
	char	hex_char;

	count = 0;
	if (n >= 16)
	{
		tmp = ft_putnbr_hex(n / 16, uppercase);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	hex_char = digit_to_hex(n % 16, uppercase);
	if (write(1, &hex_char, 1) == -1)
		return (-1);
	return (count + 1);
}
