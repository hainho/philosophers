/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:14:25 by iha               #+#    #+#             */
/*   Updated: 2022/03/15 23:34:31 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_cur_time(void)
{
	struct timeval	time;
	long long		cur_time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	cur_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (cur_time);
}

int	print_philo_state(t_info *info, t_philo *philo, int state)
{
	long long	cur_time;

	cur_time = get_cur_time();
	if (cur_time == -1)
		return (-1);
	cur_time -= info->start_time;
	pthread_mutex_lock(&(info->print_mutex));
	if (info->simul_state == 0)
	{
		pthread_mutex_unlock(&(info->print_mutex));
		return (-1);
	}
	if (state == SLEEPING)
		printf("%lld %d is sleeping\n", cur_time, philo->idx);
	else if (state == EATING)
		printf("%lld %d is eating\n", cur_time, philo->idx);
	else if (state == THINKING)
		printf("%lld %d is thinking\n", cur_time, philo->idx);
	else if (state == TAKEFORK)
		printf("%lld %d has take fork\n", cur_time, philo->idx);
	pthread_mutex_unlock(&(info->print_mutex));
	return (0);
}

static int	is_death(t_info *info, t_philo *philo)
{
	long long	cur_time;

	if (philo->eat_count != 0 && info->simul_state != 0)
	{
		cur_time = get_cur_time();
		if (cur_time == -1)
			return (-1);
		if (cur_time - philo->eat_time > info->time_to_death)
		{
			pthread_mutex_lock(&(info->print_mutex));
			printf("%lld %d died\n", cur_time - info->start_time, philo->idx);
			info->simul_state = 0;
			pthread_mutex_unlock(&(info->print_mutex));
			return (-1);
		}
	}
	return (0);
}

void	philo_death_check(t_info *info)
{
	int			idx;

	while (info->simul_state != 0)
	{
		idx = 0;
		while (idx < info->philo_num)
		{
			if (is_death(info, &(info->philos[idx])) == -1)
			{
				info->simul_state = 0;
				return ;
			}
			idx++;
		}
	}
	return ;
}

void	philo_end(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->philo_num)
		pthread_join(info->philos[idx++].thread, NULL);
	idx = 0;
	while (idx < info->philo_num)
		pthread_mutex_destroy(&(info->mutexes[idx++]));
	pthread_mutex_destroy(&(info->print_mutex));
	return ;
}