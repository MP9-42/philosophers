/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:39:42 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 23:19:09 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned int wait_time(t_table *table, int duration)
{
	unsigned long	start;

	start = get_time();
	while (!simulation_stopped(table))
	{
		if (get_time() - start >= (unsigned long)duration)
			break ;
		usleep(500);
	}
	return (get_time() - start);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->table->start_lock);
	pthread_mutex_unlock(philo->table->start_lock);
	pthread_mutex_lock(philo->table->stop_mutex);
	philo->last_meal_time = philo->table->start_time;
	pthread_mutex_unlock(philo->table->stop_mutex);
	if (philo->table->size == 1)
		return (edge_case(philo), NULL);
	if (philo->index % 2 == 0)
		wait_time(philo->table, philo->table->time_to_eat / 2);
	while (!simulation_stopped(philo->table) && !philo->isdead)
	{
		usleep(1000);
		if (eat(philo) == 0)
			return(NULL);
		if (sleep_and_think(philo) == 0)
			return (NULL);
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

int	eat(t_philo *philo)
{
	if (simulation_stopped(philo->table) || philo->isdead)
	{
		pthread_mutex_unlock(philo->right_fork.fork);
		pthread_mutex_unlock(philo->left_fork.fork);
		return (0);
	}
	take_forks(philo);
	if (print_state(philo, "is eating") == 0)
		return(0);
	philo->meals_eaten++;
	wait_time(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork.fork);
	pthread_mutex_unlock(philo->left_fork.fork);
	pthread_mutex_lock(philo->table->stop_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->table->stop_mutex);
	return (1);
}

int	sleep_and_think(t_philo *philo)
{
	if (simulation_stopped(philo->table) || philo->isdead)
		return (0);
	if (print_state(philo, "is sleeping") == 0)
		return(0);
	philo->time_sleeping = wait_time(philo->table, philo->table->time_to_sleep);
	if (print_state(philo, "is thinking") == 0)
		return(0);
	wait_time(philo->table, 1);
	return(1);
}
