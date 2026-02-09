#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include "../libft.h"
# include <pthread.h>
# include <sys/time.h> 

typedef_struct s_philo t_philo;
typedef_struct s_table t_table;

typedef struct s_philo
{
	int				meals_eaten;
	int 			index;
	long			last_meal;
	t_table			table;
	t_philo			*left_philo;
	t_philo			*right_philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}					t_philo;


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
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_t			monitor;	
}						t_table;

#endif