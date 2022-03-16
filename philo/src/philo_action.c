/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:14:13 by iha               #+#    #+#             */
/*   Updated: 2022/03/16 23:52:35 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	philo_take_fork(t_info *info, t_philo *philo)
{
	if (philo->idx % 2)
	{
		pthread_mutex_lock(philo->left);
		if (print_philo_state(info, philo, TAKEFORK) == -1)
			return (-1);
		pthread_mutex_lock(philo->right);
		if (print_philo_state(info, philo, TAKEFORK) == -1)
			return (-1);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		if (print_philo_state(info, philo, TAKEFORK) == -1)
			return (-1);
		pthread_mutex_lock(philo->left);
		if (print_philo_state(info, philo, TAKEFORK) == -1)
			return (-1);
	}
	return (0);
}

static void	philo_take_down_fork(t_philo *philo)
{
	if (philo->idx % 2)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
}

static int	philo_eat(t_info *info, t_philo *philo)
{
	long long	end_time;
	long long	cur_time;

	if (philo->eat_count > 0)
		(philo->eat_count)--;
	else if (philo->eat_count == 0)
		philo->eat_count = -1;
	if (print_philo_state(info, philo, EATING) == -1)
		return (-1);
	cur_time = get_cur_time();
	if (cur_time == -1)
		return (-1);
	philo->eat_time = cur_time;
	end_time = cur_time + info->time_to_eat;
	while (cur_time < end_time)
	{
		usleep(10);
		cur_time = get_cur_time();
		if (cur_time == -1)
			return (-1);
	}
	philo->eat_time = end_time;
	return (0);
}

static int	philo_sleep(t_info *info, t_philo *philo)
{
	long long	end_time;
	long long	cur_time;

	if (print_philo_state(info, philo, SLEEPING) == -1)
		return (-1);
	cur_time = get_cur_time();
	if (cur_time == -1)
		return (-1);
	end_time = cur_time + info->time_to_sleep;
	while (cur_time < end_time && info->simul_state != 0)
	{
		usleep(10);
		cur_time = get_cur_time();
		if (cur_time == -1)
			return (-1);
	}
	return (0);
}

void	*philo_action(void *p)
{
	t_philo	*philo;
	t_info	*info;

	philo = p;
	info = philo->info;
	while (info->simul_state != 0)
	{
		if (philo_take_fork(info, philo) == -1)
			return (NULL);
		if (philo_eat(info, philo) == -1)
			return (NULL);
		philo_take_down_fork(philo);
		if (philo_sleep(info, philo) == -1)
			return (NULL);
		if (philo->eat_count == 0 && info->simul_state != 0)
		{
			pthread_mutex_lock(&(info->state_mutex));
			info->simul_state--;
			pthread_mutex_unlock(&(info->state_mutex));
		}
	}
	return (NULL);
}
