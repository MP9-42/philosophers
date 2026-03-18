/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:23:28 by MP9               #+#    #+#             */
/*   Updated: 2026/03/18 16:09:01 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h> 
# include <limits.h>

typedef struct s_philo			t_philo;
typedef struct s_table			t_table;
typedef struct s_mutex_wrapper	t_mutex_wrapper;

typedef struct s_mutex_wrapper
{
	pthread_mutex_t	*mutex;
	int				initialized;
	int				lock;
}				t_mutex_wrapper;

typedef struct s_philo
{
	int						meals_eaten;
	int						index;
	long					last_meal_time;
	struct s_table			*table;
	t_mutex_wrapper			left_fork;
	t_mutex_wrapper			right_fork;
	pthread_t				thread;
}							t_philo;

typedef struct s_table
{
	int					size;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meal;
	int					stop;
	long				start_time;
	struct s_philo		*philos;
	t_mutex_wrapper		print_mutex;
	t_mutex_wrapper		stop_mutex;
	t_mutex_wrapper		start_lock;
	pthread_mutex_t		*forks;
	pthread_t			monitor;	
}						t_table;

// Utils
long			philo_atoli(const char *str);
void			free_all(t_table *table);
void			kill_threads(t_table *table);
void			uneven_forks(t_philo *philo);
void			even_forks(t_philo *philo);
int				ft_isdigit(char c);

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
int				simulation_stopped(t_table *table);
void			lock_mutex(t_mutex_wrapper *mutex_wrap);
void			unlock_mutex(t_mutex_wrapper *mutex_wrap);
long			get_time(void);
void			kill_mutexes(t_table *table);
int				isend(t_philo *philo);



#endif