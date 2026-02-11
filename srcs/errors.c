/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:27:55 by MP9               #+#    #+#             */
/*   Updated: 2026/02/11 13:36:55 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	error_exitpt2(int errnum, t_table *table)
{
	if (errnum == 4)
	{
		ft_printf("Couldn't allocate memory for the philos!\n");
		free(table->forks);
		free(table);
		exit(4);
	}
	else if (errnum = 5)
	{
		ft_printf("Couldn't allocate memory for the philos!\n");
		free(table->philos);
		free(table->forks);
		free(table);
		exit(5);
	}
}

void	error_exit(int errnum, t_table *table)
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
	else if(errnum == 3)
	{
		ft_printf("Couldn't allocate memory for the forks!\n");
		free(table);
		exit(3);
	}
	else
		error_exitpt2(errnum, table);
}
