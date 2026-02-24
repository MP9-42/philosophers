/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:39:42 by MP9               #+#    #+#             */
/*   Updated: 2026/02/24 14:28:27 by MP9              ###   ########.fr       */
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
		ft_printf()
	}
}
