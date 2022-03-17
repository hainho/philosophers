/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:13:48 by iha               #+#    #+#             */
/*   Updated: 2022/03/18 00:29:09 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	free_all(t_info *info, int return_value)
{
	if (info->mutexes)
		free(info->mutexes);
	if (info->philos)
		free(info->philos);
	return (return_value);
}

static void	fork_unlock_destory(t_info *info, int idx)
{
	if (pthread_mutex_destroy(&(info->mutexes[idx])) != 0)
	{
		pthread_mutex_unlock(&(info->mutexes[idx]));
		if (idx < info->philo_num)
			pthread_mutex_unlock(&(info->mutexes[idx + 1]));
		fork_unlock_destory(info, idx);
		return ;
	}
	return ;
}

static void	mutex_unlock_destory(pthread_mutex_t *m)
{
	if (pthread_mutex_destroy(m) != 0)
	{
		pthread_mutex_unlock(m);
		mutex_unlock_destory(m);
		return ;
	}
	return ;
}

void	philo_end(t_info *info)
{
	int	idx;

	idx = 0;
	mutex_unlock_destory(&(info->print_mutex));
	mutex_unlock_destory(&(info->state_mutex));
	while (idx < info->philo_num)
		fork_unlock_destory(info, idx++);
	idx = 0;
	while (idx < info->philo_num)
		pthread_join(info->philos[idx++].thread, NULL);
	return ;
}
