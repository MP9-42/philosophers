/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:38:31 by MP9               #+#    #+#             */
/*   Updated: 2026/02/11 13:34:33 by MP9              ###   ########.fr       */
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
				error_exit(1);
			si++;
		}
		si = 0;
		bi++;
	}
	if (bi < 4)
		error_exit(0);
}

void	init_mutexes(t_table *table)
{
	int i = 0;
	while (i < table->size)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
			error_exitpt2(5, table);
		i++;
	}
}

void handle_input(t_table *table, char **input)
{
	struct timeval tv;

	check_input(input);
	gettimeofday(&tv, NULL);
	table = malloc(sizeof(t_table) * 1);
	if (!table)
		error_exit(2);
	table->size = ft_atoi(input[0]);
	table->time_to_die = ft_atoi(input[1]);
	table->time_to_eat = ft_atoi(input[2]);
	table->time_to_sleep = ft_atoi(input[3]);
	if (input[4])
		table->max_meal = ft_atoi(input[4]);
	else
		table->max_meal = 0;
	table->start_time = tv.tv_usec;
	table->stop = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->size);
	if (!table->forks)
		error_exit(3);
	table->philos = malloc(sizeof(t_philo) * table->size);
	if (!table->philos)
		error_exit(4);
	init_mutexes(table);
}
