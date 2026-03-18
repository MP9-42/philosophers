/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:49:46 by MP9               #+#    #+#             */
/*   Updated: 2026/03/18 16:53:28 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutexes(t_table *table)
{
	int					i;

	i = 0;
	table->stop_mutex.mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->stop_mutex.mutex)
		error_exit(5, table);
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
	table->print_mutex.initialized = 0;
	table->stop_mutex.initialized = 0;
	init_mutexespt2(table);
}

void	init_mutexespt2(t_table *table)
{
	if (pthread_mutex_init(table->print_mutex.mutex, NULL) != 0)
		error_exitpt2(6, table);
	table->print_mutex.initialized = 1;
	table->print_mutex.lock = 0;
	if (pthread_mutex_init(table->stop_mutex.mutex, NULL) != 0)
		error_exitpt2(7, table);
	table->stop_mutex.initialized = 1;
	table->stop_mutex.lock = 0;
	table->start_lock.mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->start_lock.mutex)
		error_exitpt2(5, table);
	if (pthread_mutex_init(table->start_lock.mutex, NULL) != 0)
		error_exitpt2(9, table);
	table->start_lock.initialized = 1;
	lock_mutex(&table->start_lock);
	table->start_lock.lock = 1;
}

void	kill_mutexes(t_table *table)
{
	while ((table->size - 1) > 0)
	{
		pthread_mutex_destroy(&(table->forks[table->size - 1]));
		table->size--;
	}
	if (table->print_mutex.initialized == 1)
		pthread_mutex_destroy(table->print_mutex.mutex);
	if (table->stop_mutex.initialized == 1)
		pthread_mutex_destroy(table->stop_mutex.mutex);
	if (table->start_lock.initialized == 1)
		pthread_mutex_destroy(table->start_lock.mutex);
}

void	lock_mutex(t_mutex_wrapper *mutex_wrap)
{
	if (pthread_mutex_lock(mutex_wrap->mutex) != 0)
		printf("Error locking mutex\n");
	mutex_wrap->lock = 1;
}
