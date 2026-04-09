/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:38:31 by MP9               #+#    #+#             */
/*   Updated: 2026/04/01 19:07:35 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_input(char **input)
{
	int	bi;
	int	si;

	bi = 0;
	si = 0;
	while (input[bi] != NULL)
	{
		while (input[bi][si] != '\0')
		{
			if (input[bi][si] == ' ' || input[bi][si] == '+')
				si++;
			else if (ft_isdigit(input[bi][si]) == 0)
				error_exit(1, NULL);
			si++;
		}
		si = 0;
		bi++;
	}
	if (bi < 4)
		error_exit(0, NULL);
}

void	short_stuff(t_table *table, char **input)
{
	table->size = philo_atoli(input[0]);
	table->time_to_die = philo_atoli(input[1]);
	table->time_to_eat = philo_atoli(input[2]);
	table->time_to_sleep = philo_atoli(input[3]);
	if (input[4])
		table->max_meal = philo_atoli(input[4]);
	else
		table->max_meal = 0;
	table->stop = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->size);
	if (!table->forks)
		error_exit(3, table);
	table->philos = malloc(sizeof(t_philo) * table->size);
	if (!table->philos)
		error_exit(4, table);
	table->print_mutex.mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->print_mutex.mutex)
		error_exit(5, table);
}

t_table	*handle_input(char **input)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		error_exit(2, table);
	check_input(input);
	short_stuff(table, input);
	init_mutexes(table);
	return (table);
}
