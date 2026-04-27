/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:23:28 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 18:53:13 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include "structs.h"
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h> 
# include <limits.h>


// Utils
long			philo_atoli(const char *str);
void			free_all(t_table *table);
void			kill_threads(t_table *table);
void			uneven_forks(t_philo *philo);
void			even_forks(t_philo *philo);
int				print_state(t_philo *philo, char *msg);
int				ft_isdigit(char c);
void			wait_time(t_table *table, int duration);

// Parsing
t_table			*handle_input(char **input);
void			check_input(char **input);

// Initilization
void			init_mutexes(t_table *table);
void			init_mutexespt2(t_table *table);
void			init_philos(t_table *table);
void			init_threads(t_table *table);

//error handling
void			error_exit(int errnum, t_table *table);
void			error_exitpt2(int errnum, t_table *table);
void			error_exitpt3(int errnum, t_table *table);

// Routine
void			*philo_routine(void *arg);
void			take_forks(t_philo *philo);
void			eat(t_philo *philo);
void			sleep_and_think(t_philo *philo);
bool			simulation_stopped(t_table *table);
unsigned long	get_time(void);
void			kill_mutexes(t_table *table);
int				isend(t_philo *philo);
void			isend_helper(t_philo *philo, long elapsed_time);
void			*monitoring_routine(void *arg);
void			edge_case(t_philo *philo);
int				mutex_timedlock(pthread_mutex_t *mutex, int timeout_ms);

#endif