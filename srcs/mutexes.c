/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:49:46 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 14:34:43 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->stop_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->stop_mutex)
		error_exit(5, table);
	while (i < table->size)
	{
		if (pthread_mutex_init((&table->forks[i].fork), NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy((&table->forks[i].fork));
				i--;
			}
			error_exitpt2(5, table);
		}
		table->forks[i].taken = false;
		i++;
	}
	init_mutexespt2(table);
}

void	init_mutexespt2(t_table *table)
{
	if (pthread_mutex_init(table->print_mutex, NULL) != 0)
		error_exitpt2(6, table);
	if (pthread_mutex_init(table->stop_mutex, NULL) != 0)
		error_exitpt2(7, table);
	table->start_lock = malloc(sizeof(pthread_mutex_t));
	if (!table->start_lock)
		error_exitpt2(5, table);
	if (pthread_mutex_init(table->start_lock, NULL) != 0)
		error_exitpt2(9, table);
	pthread_mutex_lock(table->start_lock);
}

void	kill_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		pthread_mutex_destroy((&table->forks[i].fork));
		i++;
	}
	if (table->print_mutex)
		pthread_mutex_destroy(table->print_mutex);
	if (table->stop_mutex)
		pthread_mutex_destroy(table->stop_mutex);
	if (table->start_lock)
		pthread_mutex_destroy(table->start_lock);
}
