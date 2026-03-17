/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:39:42 by MP9               #+#    #+#             */
/*   Updated: 2026/03/17 20:07:56 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->index % 2 == 0)
		usleep(100);

	while (!simulation_stopped(philos->table))
	{
		eat(philos);
		sleep_and_think(philos);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		lock_mutex(&philo->right_fork);
		lock_mutex(&philo->left_fork);
	}
	else
	{
		lock_mutex(&philo->left_fork);
		lock_mutex(&philo->right_fork);
	}
	ft_printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	ft_printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	lock_mutex(&philo->table->print_mutex);
	ft_printf("%ld %d is eating\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	usleep(philo->table->time_to_eat);
	unlock_mutex(&philo->left_fork);
	unlock_mutex(&philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	lock_mutex(&philo->table->print_mutex);
	ft_printf("%ld %d is sleeping\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	usleep(philo->table->time_to_sleep);
	lock_mutex(&philo->table->print_mutex);
	ft_printf("%ld %d is thinking\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
}