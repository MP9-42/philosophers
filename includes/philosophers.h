/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:23:28 by MP9               #+#    #+#             */
/*   Updated: 2026/02/23 17:29:33 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h> 

typedef struct s_philo			t_philo;
typedef struct s_table			t_table;
typedef struct s_mutex_wrapper	t_mutex_wrapper;

typedef struct s_mutex_wrapper
{
	pthread_mutex_t	mutex;
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
	long				start_time;
	int					stop;
	pthread_mutex_t		*forks;
	struct s_philo		*philos;
	t_mutex_wrapper		print_mutex;
	t_mutex_wrapper		stop_mutex;
	pthread_t			monitor;	
}						t_table;

// Utils
long	philo_atoli(const char *str);
void	free_all(t_table *table);
void	kill_threads(t_table *table);

// Parsing
void	handle_input(t_table *table, char **input);
void	check_input(char **input);

// Initilization
void	init_mutexes(t_table *table);
void	init_mutexespt2(t_table *table);
void	init_philos(t_table *table);
void	init_threads(t_table *table);


//error handling
void	error_exit(int errnum, t_table *table);
void	error_exitpt2(int errnum, t_table *table);
void	error_exitpt3(int errnum, t_table *table);

#endif