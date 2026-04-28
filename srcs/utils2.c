/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:37:45 by MP9               #+#    #+#             */
/*   Updated: 2026/04/28 20:27:43 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	all_meals_done(t_table *table)
{
	int	i;
	int	has_meal;

	i = 0;
	has_meal = 0;
	if (table->max_meal <= 0)
		return (0);
	while (i < table->size)
	{
		if (table->philos[i].meals_eaten < table->max_meal)
			return (0);
		i++;
	}
	return (1);
}

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
	if (elapsed_time >= philo->table->time_to_die)
	{
		print_state(philo, "died");
		philo->table->stop = true;
		philo->isdead = true;
		pthread_mutex_unlock(philo->table->stop_mutex);
		return (1);
	}
	else if (all_meals_done(philo->table))
	{
		print_state(philo, "has eaten all meals!");
		philo->table->stop = true;
		pthread_mutex_unlock(philo->table->stop_mutex);
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
		usleep(1500);
	}
	return (NULL);
}
