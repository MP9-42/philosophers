/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:50:56 by MP9               #+#    #+#             */
/*   Updated: 2026/04/28 19:30:03 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	philo_atoli(const char *str)
{
	long	num;
	int		prepoc;

	num = 0;
	prepoc = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			prepoc *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num < INT_MIN || num > INT_MAX)
		return (-1);
	return (prepoc * num);
}

void	free_all(t_table *table)
{
    
	if (table->start_lock)
		free(table->start_lock);
	if (table->stop_mutex)
		free(table->stop_mutex);
	if (table->print_mutex)
		free(table->print_mutex);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	free(table);
}

unsigned long	get_time(void)
{
	struct timeval		tv;
	unsigned long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

bool	simulation_stopped(t_table *table)
{
	bool	stopped;

	pthread_mutex_lock(table->stop_mutex);
	stopped = table->stop;
	pthread_mutex_unlock(table->stop_mutex);
	return (stopped);
}
