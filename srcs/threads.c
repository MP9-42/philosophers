/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:01:29 by MP9               #+#    #+#             */
/*   Updated: 2026/02/23 17:23:14 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutexes(t_table *table)
{
	int					i;

	i = 0;
	if (table->time_to_sleep < 60000 || table->time_to_die < 60000
		|| table->time_to_eat < 60000)
		error_exit(5, table);
	while (i < table->size)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&(table->forks[i]));
				i--;
			}
			error_exitpt2(5, table);
		}
		i++;
	}
}

void	init_mutexespt2(t_table *table)
{
	if (pthread_mutex_init(&(table->print_mutex.mutex), NULL) != 0)
		error_exitpt2(6, table);
	table->print_mutex.initialized = 1;
	table->print_mutex.lock == 0;
	if (pthread_mutex_init(&(table->stop_mutex.mutex), NULL) != 0)
		error_exitpt2(7, table);
	table->stop_mutex.initialized = 1;
	table->stop_mutex.lock == 0;
}

void	init_philos(t_table *table)
{
	int				i;
	struct timeval	tv;

	i = 0;
	gettimeofday(&tv, NULL);
	table->start_time = tv.tv_usec * 1000;
	while (i < table->size)
	{
		table->philos[i].index = i;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		table->philos->left_fork.mutex = table->forks[i];
		table->philos->left_fork.initialized = 1;
		table->philos->left_fork.lock = 0;
		table->philos->right_fork.mutex = table->forks[(i + 1) % table->size];
		table->philos->right_fork.initialized = 1;
		table->philos->right_fork.lock = 0;
		i++;
	}
}

void	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		if (pthread_create(&(table->philos[i].thread), NULL,
				routine, &table->philos[i]) != 0)
			error_exitpt2(8, table);
		i++;
	}

}