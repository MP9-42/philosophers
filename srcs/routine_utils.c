/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:03:57 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 23:14:54 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	even_forks(t_philo *philo)
{
	if (!philo->right_fork.taken)
		pthread_mutex_lock(philo->right_fork.fork);
	print_state(philo, "has taken a fork");
	if (!philo->right_fork.taken)
	pthread_mutex_lock(philo->left_fork.fork);
}

void	uneven_forks(t_philo *philo)
{
	if (!philo->left_fork.taken)
		pthread_mutex_lock(philo->left_fork.fork);
	print_state(philo, "has taken a fork");
	if (!philo->right_fork.taken)
		pthread_mutex_lock(philo->right_fork.fork);
}

void	edge_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork.fork);
	if (print_state(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(philo->left_fork.fork);
		print_state(philo, "has died!");
		return ;
	}
	while (!simulation_stopped(philo->table))
		usleep(500);
	pthread_mutex_unlock(philo->left_fork.fork);
}
