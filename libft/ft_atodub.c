/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:56:28 by MP9               #+#    #+#             */
/*   Updated: 2025/10/13 15:39:50 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	atodub_support(char *str, int *i)
{
	double	decimal;
	double	result;

	decimal = 0.1;
	result = 0.0;
	(*i)++;
	while (ft_isdigit(str[*i]))
	{
		result += (str[*i] - '0') * decimal;
		decimal *= 0.1;
		(*i)++;
	}
	return (result);
}

double	ft_atodub(char *str)
{
	double	num;
	int		prepoc;
	int		i;

	i = 0;
	num = 0;
	prepoc = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			prepoc = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = num * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		num += atodub_support(str, &i);
	return (prepoc * num);
}
