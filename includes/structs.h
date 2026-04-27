/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:43:04 by MP9               #+#    #+#             */
/*   Updated: 2026/04/27 19:08:09 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo			t_philo;
typedef struct s_table			t_table;
typedef struct s_fork			t_fork;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			taken;
}					t_fork;

typedef struct s_philo
{
	int				meals_eaten;
	int				index;
	int				time_sleeping;
	int				time_thinking;
	unsigned long	last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table			*table;
	pthread_t		thread;
	bool			isdead;

}					t_philo;

typedef struct s_table
{
	unsigned long	start_time;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				size;
	int				max_meal;
	bool			stop;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*start_lock;
	pthread_mutex_t	*stop_mutex;
	pthread_t		monitor;
}					t_table;

#endif