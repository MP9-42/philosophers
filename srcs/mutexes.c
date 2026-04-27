/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:49:46 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 20:34:35 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		table->forks[i].fork = malloc(sizeof(pthread_mutex_t));
		if (!table->forks[i].fork)
		{
			while (i-- > 0)
			{
				pthread_mutex_destroy(table->forks[i].fork);
				free(table->forks[i].fork);
			}
			error_exitpt2(5, table);
		}
		if (pthread_mutex_init(table->forks[i].fork, NULL) != 0)
		{
			free(table->forks[i].fork);
			while (i-- > 0)
			{
				pthread_mutex_destroy(table->forks[i].fork);
				free(table->forks[i].fork);
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
		if (table->forks[i].fork)
		{
			pthread_mutex_destroy(table->forks[i].fork);
			free(table->forks[i].fork);
		}
		i++;
	}
	if (table->print_mutex)
		pthread_mutex_destroy(table->print_mutex);
	if (table->stop_mutex)
		pthread_mutex_destroy(table->stop_mutex);
	if (table->start_lock)
		pthread_mutex_destroy(table->start_lock);
}
