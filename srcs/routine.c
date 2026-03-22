/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:39:42 by MP9               #+#    #+#             */
/*   Updated: 2026/03/22 17:52:12 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->table->size == 1)
		edge_case(philos);
	lock_mutex(&philos->table->start_lock);
	unlock_mutex(&philos->table->start_lock);
	while (simulation_stopped(philos->table) != 1
		&& philos->table->stop_mutex.lock != 1)
	{
		eat(philos);
		sleep_and_think(philos);
	}
	kill_threads(philos->table);
	free_all(philos->table);
	exit(5);
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if ((philo->index + 1) % 2 == 0)
		even_forks(philo);
	else
		uneven_forks(philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	unlock_mutex(&philo->left_fork);
	unlock_mutex(&philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	mutex_timedlock(&philo->table->print_mutex, philo->table->time_to_sleep);
	printf("%ld %d is sleeping\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
}
