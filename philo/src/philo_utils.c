/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:14:25 by iha               #+#    #+#             */
/*   Updated: 2022/03/19 15:28:06 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_cur_time(t_info *info)
{
	struct timeval	time;
	long long		cur_time;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&(info->state_mutex));
		info->simul_state = 0;
		pthread_mutex_unlock(&(info->state_mutex));
		return (-1);
	}
	cur_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (cur_time);
}

int	print_philo_state(t_info *info, t_philo *philo, int state)
{
	long long	cur_time;
	
	pthread_mutex_lock(&(info->print_mutex));
	cur_time = get_cur_time(info);
	if (cur_time == -1)
	{
		pthread_mutex_unlock(&(info->print_mutex));
		return (-1);
	}
	cur_time -= info->start_time;
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

	if (info->simul_state != 0)
	{
		pthread_mutex_lock(&(info->print_mutex));
		cur_time = get_cur_time(info);
		if (cur_time == -1)
			return (-1);
		if (cur_time - philo->eat_time > info->time_to_death)
		{
			printf("%lld %d died\n", cur_time - info->start_time, philo->idx);
			pthread_mutex_lock(&(info->state_mutex));
			info->simul_state = 0;
			pthread_mutex_unlock(&(info->state_mutex));
			return (-1);
		}
		pthread_mutex_unlock(&(info->print_mutex));
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
				pthread_mutex_lock(&(info->state_mutex));
				info->simul_state = 0;
				pthread_mutex_unlock(&(info->state_mutex));
				return ;
			}
			idx++;
		}
	}
	return ;
}
