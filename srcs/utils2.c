/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:37:45 by MP9               #+#    #+#             */
/*   Updated: 2026/03/18 16:11:34 by MP9              ###   ########.fr       */
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
	if (philo->last_meal_time == philo->table->time_to_die
		|| philo->meals_eaten == philo->table->max_meal)
	{
		lock_mutex(&philo->table->stop_mutex);
		lock_mutex(&philo->table->print_mutex);
		if (philo->last_meal_time == philo->table->time_to_die)
			printf("%ld %d has died!\n",
				get_time() - philo->table->start_time, philo->index + 1);
		else
			printf("%ld %d has eaten all meals!\n",
				get_time() - philo->table->start_time, philo->index + 1);
		unlock_mutex(&philo->table->print_mutex);
		return (1);
	}
	return (0);
}
