/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:01:29 by MP9               #+#    #+#             */
/*   Updated: 2026/03/18 14:33:25 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philos(t_table *table)
{
	int				i;

	i = 0;
	table->start_time = get_time();
	while (i < table->size)
	{
		table->philos[i].index = i;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork.mutex = &table->forks[i];
		table->philos[i].left_fork.initialized = 1;
		table->philos[i].left_fork.lock = 0;
		table->philos[i].right_fork.mutex
			= &table->forks[(i + 1) % table->size];
		table->philos[i].right_fork.initialized = 1;
		table->philos[i].right_fork.lock = 0;
		i++;
	}
	init_threads(table);
}

void	init_threads(t_table *table)
{
	int		i;
	void	*gimmedat;

	i = 0;
	gimmedat = (void *)table;
	while (i < table->size)
	{
		if (pthread_create(&(table->philos[i].thread), NULL,
				philo_routine, &table->philos[i]) != 0)
			error_exitpt2(8, table);
		if (table->philos[i].index % 2 == 0)
			usleep(100);
		i++;
	}
}

void	kill_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			printf("Error: failed to join thread %d\n", i);
		i++;
	}
	kill_mutexes(table);
}

void	unlock_mutex(t_mutex_wrapper *mutex_wrap)
{
	if (pthread_mutex_unlock(mutex_wrap->mutex) != 0)
		printf("Error unlocking mutex\n");
	mutex_wrap->lock = 0;
}
