/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:42:26 by MP9               #+#    #+#             */
/*   Updated: 2026/02/11 13:50:36 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	edge_case(long num)
{
	if (num == LONG_MIN)
	{
		if (write(1, "-9223372036854775808", 20) == -1)
			return(-1);
	}
	return(20);
}

int	ft_putlong(long num)
{
	char	digit;
	int		count;
	int		temp;

	count = 0;
	if (num == LONG_MIN)
		return (edge_case(num));
	if (num < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		count++;
		num = -num;
	}
	if (num >= 10)
	{
		temp = ft_putnbr(num / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	digit = '0' + (num % 10);
	if (write(1, &digit, 1) == -1)
		return (-1);
	return (count + 1);
}
