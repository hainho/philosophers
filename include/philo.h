#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SLEEPING 0
# define THINKING 1

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				idx;
	long long		eat_time;
	int				state;
}	t_philo;

typedef struct	s_info
{
	t_philo			*philos;
	pthread_mutex_t	*mutexes;
	long long		start_time;
	int				eat_time;
	int				death_time;
	int				sleep_time;
	int				eat_count;
}	t_info;

#endif
