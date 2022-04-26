/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:14:30 by iha               #+#    #+#             */
/*   Updated: 2022/03/29 13:55:40 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_philo(t_info *info, t_philo *philo, int idx)
{
	philo->info = info;
	philo->eat_time = 0;
	philo->idx = idx + 1;
	philo->eat_count = info->eat_count;
	philo->left = &(info->mutexes[idx]);
	if (idx == info->philo_num - 1)
		philo->right = &(info->mutexes[0]);
	else
		philo->right = &(info->mutexes[idx + 1]);
	return ;
}

static int	philo_run(t_info *info, int idx)
{
	void	*temp;

	info->philos[idx].eat_time = info->start_time;
	temp = &(info->philos[idx]);
	if (pthread_create(&(info->philos[idx].thread), \
	NULL, philo_action, temp))
		return (-1);
	return (0);
}

int	philo_run_all(t_info *info)
{
	int		idx;

	idx = 0;
	info->start_time = get_cur_time(info);
	if (info->start_time == -1)
		return (-1);
	while (idx < info->philo_num)
	{
		if (philo_run(info, idx) == -1)
			return (-1);
		idx += 2;
	}
	usleep(1000);
	idx = 1;
	while (idx < info->philo_num)
	{
		if (philo_run(info, idx) == -1)
			return (-1);
		idx += 2;
	}
	return (0);
}
