/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:37:45 by MP9               #+#    #+#             */
/*   Updated: 2026/04/09 21:37:26 by MP9              ###   ########.fr       */
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

	now = get_time();
	elapsed_time = now - philo->last_meal_time;
	if (elapsed_time > philo->table->time_to_die
		|| (philo->meals_eaten == philo->table->max_meal
			&& philo->meals_eaten >= 1))
	{
		isend_helper(philo, elapsed_time);
		return (philo->table->stop);
	}
	return (0);
}

void	isend_helper(t_philo *philo, long elapsed_time)
{
	if (elapsed_time > philo->table->time_to_die)
	{
		lock_mutex(&philo->table->stop_mutex);
		lock_mutex(&philo->table->print_mutex);
		printf("%ld %d has died!\n",
			get_time() - philo->table->start_time, philo->index + 1);
		unlock_mutex(&philo->table->print_mutex);
		philo->table->stop = 1;
	}
	else
	{
		lock_mutex(&philo->table->stop_mutex);
		lock_mutex(&philo->table->print_mutex);
		printf("%ld %d has eaten all meals!\n",
			get_time() - philo->table->start_time, philo->index + 1);
		unlock_mutex(&philo->table->print_mutex);
		philo->table->stop = 1;
		printf("%lu isend: philo %d set table->stop=1\n",
			get_time() - philo->table->start_time, philo->index + 1);
	}
}

void	*monitoring_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (table->stop == 1 || table->stop_mutex.lock == 1)
		{
			/* stop requested; return so main can join and cleanup */
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
