/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:03:57 by MP9               #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	even_forks(t_philo *philo)
{
	lock_mutex(&philo->right_fork);
	if (print_state(philo, "has taken a fork") == 0)
	{
		unlock_mutex(&philo->right_fork);
		return ;
	}
	lock_mutex(&philo->left_fork);
	if (print_state(philo, "has taken a fork") == 0)
	{
		unlock_mutex(&philo->left_fork);
		unlock_mutex(&philo->right_fork);
	}
}

void	uneven_forks(t_philo *philo)
{
	lock_mutex(&philo->left_fork);
	if (print_state(philo, "has taken a fork") == 0)
	{
		unlock_mutex(&philo->left_fork);
		return ;
	}
	lock_mutex(&philo->right_fork);
	if (print_state(philo, "has taken a fork") == 0)
	{
		unlock_mutex(&philo->right_fork);
		unlock_mutex(&philo->left_fork);
	}
}

void	edge_case(t_philo *philo)
{
	lock_mutex(&philo->left_fork);
	if (print_state(philo, "has taken a fork") == 0)
	{
		unlock_mutex(&philo->left_fork);
		return ;
	}
	while (simulation_stopped(philo->table) == 0)
		usleep(500);
	unlock_mutex(&philo->left_fork);
}
