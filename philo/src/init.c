/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:13:59 by iha               #+#    #+#             */
/*   Updated: 2022/03/15 23:14:08 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_mutex(t_info *info)
{
	int	idx;

	info->mutexes = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (info->mutexes == NULL)
		return (-1);
	idx = 0;
	while (idx < info->philo_num)
	{
		if (pthread_mutex_init(&(info->mutexes[idx++]), NULL) != 0)
			return (-1);
	}
	if (pthread_mutex_init(&(info->print_mutex), NULL) != 0)
		return (-1);
	return (0);
}

static int	init_philo(t_info *info)
{
	int	idx;

	info->philos = malloc(sizeof(t_philo) * info->philo_num);
	if (info->philos == NULL)
		return (-1);
	idx = 0;
	while (idx < info->philo_num)
	{
		set_philo(info, &(info->philos[idx]), idx);
		idx++;
	}
	return (0);
}

static int	init_info(t_info *info, int argc, char **argv)
{
	info->mutexes = NULL;
	info->philos = NULL;
	info->philo_num = ft_atol(argv[1]);
	info->simul_state = info->philo_num;
	info->time_to_death = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	info->eat_count = 0;
	if (argc == 6)
		info->eat_count = ft_atol(argv[5]);
	if (check_input(info) == -1)
		return (-1);
	if (argc == 5)
		info->eat_count = -1;
	return (0);
}

int	init(t_info *info, int argc, char **argv)
{
	if (init_info(info, argc, argv) == -1)
		return (-1);
	if (init_mutex(info) == -1)
		return (-1);
	if (init_philo(info) == -1)
		return (-1);
	return (0);
}
