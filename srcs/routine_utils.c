/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:03:57 by MP9               #+#    #+#             */
/*   Updated: 2026/04/28 00:00:00 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	even_forks(t_philo *philo)
{
	if (!philo->right_fork.taken)
	{
		pthread_mutex_lock(philo->right_fork.fork);
		philo->right_fork.taken = true;
		print_state(philo, "has taken a fork");
	}
	if (!philo->left_fork.taken)
	{
		pthread_mutex_lock(philo->left_fork.fork);
		philo->left_fork.taken = true;
		print_state(philo, "has taken a fork");
	}
}

void	uneven_forks(t_philo *philo)
{
	if (!philo->left_fork.taken)
	{
		pthread_mutex_lock(philo->left_fork.fork);
		philo->left_fork.taken = true;
		print_state(philo, "has taken a fork");
	}
	if (!philo->right_fork.taken)
	{
		pthread_mutex_lock(philo->right_fork.fork);
		philo->right_fork.taken = true;
		print_state(philo, "has taken a fork");
	}
}

void	edge_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork.fork);
	philo->left_fork.taken = true;
	if (print_state(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(philo->left_fork.fork);
		philo->left_fork.taken = false;
		print_state(philo, "has died!");
		return ;
	}
	while (!simulation_stopped(philo->table))
		usleep(500);
	pthread_mutex_unlock(philo->left_fork.fork);
	philo->left_fork.taken = false;
}
