#include "philo.h"

void	set_philo(t_info *info, t_philo *philo, int idx)
{
	philo->eat_time = 0;
	philo->idx = idx;
	philo->left = &(info->mutexes[idx]);
	if (idx == info->philo_num - 1)
		philo->right = &(info->mutexes[0]);
	else
		philo->right = &(info->mutexes[idx + 1]);
	philo->state = THINKING;
}
