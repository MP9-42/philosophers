/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:39:42 by MP9               #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	wait_time(t_table *table, int duration)
{
	unsigned long	start;

	start = get_time();
	while (simulation_stopped(table) == 0)
	{
		if (get_time() - start >= (unsigned long)duration)
			break ;
		usleep(500);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	lock_mutex(&philo->table->start_lock);
	unlock_mutex(&philo->table->start_lock);
	lock_mutex(&philo->table->stop_mutex);
	philo->last_meal_time = get_time();
	unlock_mutex(&philo->table->stop_mutex);
	if (philo->table->size == 1)
		return (edge_case(philo), NULL);
	if (philo->index % 2 == 0)
		wait_time(philo->table, philo->table->time_to_eat / 2);
	while (simulation_stopped(philo->table) == 0)
	{
		eat(philo);
		if (simulation_stopped(philo->table) == 1)
			break ;
		sleep_and_think(philo);
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
	if (simulation_stopped(philo->table) == 1
		|| print_state(philo, "is eating") == 0)
	{
		if (philo->left_fork.lock == 1)
			unlock_mutex(&philo->left_fork);
		if (philo->right_fork.lock == 1)
			unlock_mutex(&philo->right_fork);
		return ;
	}
	lock_mutex(&philo->table->stop_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	unlock_mutex(&philo->table->stop_mutex);
	wait_time(philo->table, philo->table->time_to_eat);
	unlock_mutex(&philo->right_fork);
	unlock_mutex(&philo->left_fork);
}

void	sleep_and_think(t_philo *philo)
{
	if (print_state(philo, "is sleeping") == 0)
		return ;
	wait_time(philo->table, philo->table->time_to_sleep);
	if (philo->table->size % 2 != 0)
		wait_time(philo->table, philo->table->time_to_eat / 2);
	print_state(philo, "is thinking");
}
