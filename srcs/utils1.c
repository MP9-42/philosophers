/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:50:56 by MP9               #+#    #+#             */
/*   Updated: 2026/02/23 14:43:07 by MP9              ###   ########.fr       */
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
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	free(table);
}

void	kill_threads(t_table *table)
{
	while ((table->size - 1) > 0)
	{
		if (table->forks[table->size - 1].initialized == 1
			&& table->forks[table->size - 1].lock == 0)
			pthread_mutex_destroy(&(table->forks[table->size - 1]));
		table->size--;
	}
	if (table->print_mutex.initialized == 1 && table->print_mutex.lock == 0)
		pthread_mutex_destroy(&table->print_mutex);
	if (table->stop_mutex.initialized == 1 && table->stop_mutex.lock == 0)
		pthread_mutex_destroy(&table->stop_mutex);
}
