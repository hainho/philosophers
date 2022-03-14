#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define SLEEPING 0
# define THINKING 1
# define EATING 2
# define TAKEFORK 3

typedef struct s_philo
{
	t_info			*info;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				idx;
	long long		eat_time;
	long long		eat_count;
	int				state;
}	t_philo;

typedef struct	s_info
{
	t_philo			*philos;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	print_mutex;
	long long		start_time;
	long long		time_to_eat;
	long long		time_to_death;
	long long		time_to_sleep;
	long long		eat_count;
	long long		philo_num;
	long long		simul_state;
}	t_info;

// philo_action.c
void	philo_action(void *p);

// validation.c
int		check_input(t_info *info);

// philo.c
void	set_philo(t_info *info, t_philo *philo, int idx);
int	philo_run(t_info *info);

// init.c
int	init(t_info *info, int argc, char **argv);

// free.c
int	free_all(t_info *info, int return_value);

// ft_utils.c
long long	ft_atol(const char *str);

// philo_utils.c
long long	get_cur_time();
int	print_philo_state(t_info *info, t_philo *philo, int state);
void	philo_death_check(t_info *info);
void	philo_end(t_info *info);

#endif
