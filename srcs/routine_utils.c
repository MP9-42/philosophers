/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:03:57 by MP9               #+#    #+#             */
/*   Updated: 2026/03/18 14:35:06 by MP9              ###   ########.fr       */
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
	lock_mutex(&philo->left_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
}

void	uneven_forks(t_philo *philo)
{
	lock_mutex(&philo->left_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
	lock_mutex(&philo->right_fork);
	lock_mutex(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->table->start_time, philo->index + 1);
	unlock_mutex(&philo->table->print_mutex);
}
