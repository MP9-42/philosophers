/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:01:29 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 19:08:09 by MP9              ###   ########.fr       */
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
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->size];
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
		usleep(100);
		i++;
	}
	if (pthread_create(&(table->monitor), NULL,
			monitoring_routine, table) != 0)
		error_exitpt2(8, table);
	pthread_mutex_unlock(table->start_lock);
}

void	kill_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			printf("Error: failed to join philosopher thread\n");
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		printf("Error: failed to join monitor thread\n");
	kill_mutexes(table);
}

int	print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->table->stop_mutex);
	pthread_mutex_lock(philo->table->print_mutex);
	if (philo->table->stop)
	{
		if (philo->isdead)
			printf("%ld %d %s\n", get_time() - philo->table->start_time,
				philo->index + 1, msg);
		pthread_mutex_unlock(philo->table->print_mutex);
		pthread_mutex_unlock(philo->table->stop_mutex);
		return (0);
	}
	printf("%ld %d %s\n", get_time() - philo->table->start_time,
		philo->index + 1, msg);
	pthread_mutex_unlock(philo->table->print_mutex);
	pthread_mutex_unlock(philo->table->stop_mutex);
	return (1);
}
