/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:38:31 by MP9               #+#    #+#             */
/*   Updated: 2026/02/17 01:32:31 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void check_input(char **input)
{
	int bi;
	int si;
	
	bi = 0;
	si = 0;
	while(input[bi] != NULL)
	{
		while(input[bi][si] != '\0')
		{
			if (input[bi][si] == ' ' || input[bi][si] == '+')
				si++;
			else if (ft_isdigit(input[bi][si]) == 0)
				error_exit(1, NULL);
			si++;
		}
		si = 0;
		bi++;
	}
	if (bi < 4)
		error_exit(0, NULL);
}

void	init_mutexes(t_table *table)
{
	int i = 0;
	if (table->time_to_sleep < 60000 || table->time_to_die < 60000
			|| table->time_to_eat < 60000)
			error_exit(5, table);
	while (i < table->size)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&(table->forks[i]));
				i--;
			}
			error_exitpt2(5, table);			
		}
		i++;
	}
	if (pthread_mutex_init(&(table->print_mutex), NULL) != 0)
		error_exitpt2(6, table);	
	if (pthread_mutex_init(&(table->stop_mutex), NULL) != 0)
		error_exitpt2(7, table);	
	if (pthread_create(&(table->monitor), NULL, /*insert func here*/, NULL) != 0)
		error_exitpt2(8, table);
}

void handle_input(t_table *table, char **input)
{
	struct timeval tv;

	check_input(input);
	gettimeofday(&tv, NULL);
	table = malloc(sizeof(t_table) * 1);
	if (!table)
		error_exit(2, table);
	table->size = philo_atoli(input[0]);
	table->time_to_die = philo_atoli(input[1]) * 1000;
	table->time_to_eat = philo_atoli(input[2]) * 1000;
	table->time_to_sleep = philo_atoli(input[3]) * 1000;
	if (input[4])
		table->max_meal = philo_atoli(input[4]);
	else
		table->max_meal = 0;
	table->start_time = tv.tv_usec;
	table->stop = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->size);
	if (!table->forks)
		error_exit(3, table);
	table->philos = malloc(sizeof(t_philo) * table->size);
	if (!table->philos)
		error_exit(4, table);
	init_mutexes(table);
}
