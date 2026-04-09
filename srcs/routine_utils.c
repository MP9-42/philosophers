/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:03:57 by MP9               #+#    #+#             */
/*   Updated: 2026/04/09 22:04:17 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	even_forks(t_philo *philo)
{
	lock_mutex(&philo->right_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	if (get_time() - philo->last_meal_time
		>= (unsigned long)philo->table->time_to_die)
	{
		unlock_mutex(&philo->right_fork);
		return ;
	}
	lock_mutex(&philo->left_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	if (get_time() - philo->last_meal_time
		>= (unsigned long)philo->table->time_to_die)
	{
		unlock_mutex(&philo->left_fork);
		unlock_mutex(&philo->right_fork);
		return ;
	}
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d is eating\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	usleep(philo->table->time_to_eat * 1000);
	unlock_mutex(&philo->left_fork);
	unlock_mutex(&philo->right_fork);
}

void	uneven_forks(t_philo *philo)
{
	lock_mutex(&philo->left_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	if (get_time() - philo->last_meal_time
		>= (unsigned long)philo->table->time_to_die)
	{
		unlock_mutex(&philo->left_fork);
		return ;
	}
	lock_mutex(&philo->right_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	if (get_time() - philo->last_meal_time
		>= (unsigned long)philo->table->time_to_die)
	{
		unlock_mutex(&philo->right_fork);
		unlock_mutex(&philo->left_fork);
		return ;
	}
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d is eating\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	usleep(philo->table->time_to_eat * 1000);
	unlock_mutex(&philo->right_fork);
	unlock_mutex(&philo->left_fork);
}

int	mutex_timedlock(t_mutex_wrapper *mutex, int timeout_ms)
{
	long	start_time;
	long	elapsed_time;

	start_time = get_time();
	while (1)
	{
		lock_mutex(mutex);
		elapsed_time = get_time() - start_time;
		if (elapsed_time >= timeout_ms)
			return (1);
		usleep(500);
		break ;
	}
	return (0);
}

void	edge_case(t_philo *philo)
{
	lock_mutex(&philo->left_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	usleep(philo->table->time_to_die * 1000);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has died!\n", get_time() - philo->table->start_time,
		philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	kill_mutexes(philo->table);
	free_all(philo->table);
	exit(5);
}
