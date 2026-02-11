#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h> 

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_philo
{
	int						meals_eaten;
	int 					index;
	long					last_meal_time;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
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
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_t			monitor;	
}						t_table;


// Parsing
void	handle_input(t_table *table, char **input);
void 	check_input(char **input);
void	init_mutexes(t_table *table);


//error handling
void	error_exit(int errnum, t_table *table);
void	error_exitpt2(int errnum, t_table *table);



#endif