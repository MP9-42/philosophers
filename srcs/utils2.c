/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:37:45 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 23:06:35 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	isend(t_philo *philo)
{
	long			elapsed_time;
	unsigned long	now;

	pthread_mutex_lock(philo->table->stop_mutex);
	now = get_time();
	elapsed_time = now - philo->last_meal_time;
	if (philo->table->max_meal > 0
		&& philo->meals_eaten >= philo->table->max_meal)
	{
		philo->table->stop = true;
		pthread_mutex_unlock(philo->table->stop_mutex);
		print_state(philo, "has eaten all meals!");
		return (1);
	}
	if (elapsed_time > philo->table->time_to_die - 1)
	{
		philo->table->stop = true;
		pthread_mutex_unlock(philo->table->stop_mutex);
		philo->isdead = true;
		print_state(philo, "died!");
		return (1);
	}
	pthread_mutex_unlock(philo->table->stop_mutex);
	return (0);
}

void	*monitoring_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	
	while (1)
	{
		i = 0;
		while (i < table->size && !simulation_stopped(table))
		{
			if (isend(&table->philos[i]) == 1)
				return (NULL);
			i++;
		}
		usleep(1200);
	}
	return (NULL);
}
