/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:39:42 by MP9               #+#    #+#             */
/*   Updated: 2026/04/09 22:04:17 by MP9              ###   ########.fr       */
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
	philos->last_meal_time = get_time();
	while (philos->table->stop == 0)
	{
		if (get_time() - philos->last_meal_time
			>= (unsigned long)philos->table->time_to_die)
		{
			lock_mutex(&philos->table->stop_mutex);
			lock_mutex(&philos->table->print_mutex);
			printf("%ld %d has died!\n",
				get_time() - philos->table->start_time, philos->index + 1);
			unlock_mutex(&philos->table->print_mutex);
			philos->table->stop = 1;
			unlock_mutex(&philos->table->stop_mutex);
			break ;
		}
		eat(philos);
		if (philos->table->max_meal > 0
			&& philos->meals_eaten >= philos->table->max_meal)
		{
			lock_mutex(&philos->table->stop_mutex);
			philos->table->stop = 1;
			unlock_mutex(&philos->table->stop_mutex);
			break ;
		}
		sleep_and_think(philos);
	}
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
}

void	sleep_and_think(t_philo *philo)
{
	unsigned long	start_sleep;

	start_sleep = get_time();
	while (get_time() - start_sleep
		< (unsigned long)philo->table->time_to_sleep)
	{
		if (get_time() - philo->last_meal_time
			>= (unsigned long)philo->table->time_to_die)
			return ;
		usleep(100);
	}
	if (get_time() - philo->last_meal_time
		< (unsigned long)philo->table->time_to_die)
	{
		lock_mutex(&philo->table->print_mutex);
		printf("%ld %d is thinking\n",
			get_time() - philo->table->start_time, philo->index + 1);
		unlock_mutex(&philo->table->print_mutex);
	}
}
