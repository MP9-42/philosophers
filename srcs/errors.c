/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:27:55 by MP9               #+#    #+#             */
/*   Updated: 2026/02/09 13:49:56 by MP9              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "includes/philosophers.h"

void error_exit(int errnum)
{
	if (errnum == 0)
	{
		ft_printf("Wrong user input!\nUsage: ./philosophers <num_of_philos>");
		ft_printf("<time_to_die> <time_to_eat> <time_to_sleep> [optional: num of meals]\n");
		exit(0);
	}
	else if (errnum == 1)
	{
		ft_printf("Wrong user input!\nPlease use positive numeric values!\n");
		exit(1);
	}
	else if (errnum == 2)
	{
		ft_printf("Couldn't allocate memory for the table!\n");
		exit(2);
	}
}