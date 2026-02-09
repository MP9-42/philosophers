/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:35:51 by MP9               #+#    #+#             */
/*   Updated: 2025/11/05 20:51:59 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrixlen(char **matrix)
{
	int	i;
	int	i2;
	int	i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	while (matrix[i])
	{
		while (matrix[i][i2] != '\0')
			i2++;
		i3 += i2;
		i2 = 0;
		i++;
	}
	if (i3 + i >= INT_MAX)
		return (0);
	return (i3 + i);
}
