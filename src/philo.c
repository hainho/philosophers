#include "philo.h"

void	set_philo(t_info *info, t_philo *philo, int idx)
{
	philo->info = info;
	philo->eat_time = 0;
	philo->idx = idx + 1;
	philo->left = &(info->mutexes[idx]);
	if (idx == info->philo_num - 1)
		philo->right = &(info->mutexes[0]);
	else
		philo->right = &(info->mutexes[idx + 1]);
	philo->state = THINKING;
}

int	philo_run(t_info *info)
{
	int		idx;
	void	*temp;

	idx = 0;
	info->start_time = get_cur_time();
	if (info->start_time == -1)
		return (-1);
	while (idx < info->philo_num)
	{
		info->philos[idx].eat_time = get_cur_time();
		if (info->philos[idx].eat_time == -1)
			return (-1);
		temp = &(info->philos[idx]);
		if (pthread_create(&(info->philos[idx++]), NULL, philo_action, temp))
			return (-1);
	}
	return (0);
}
