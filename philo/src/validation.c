/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:14:36 by iha               #+#    #+#             */
/*   Updated: 2022/03/15 23:14:36 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_input(t_info *info)
{
	if (info->philo_num < 1 || info->time_to_death < 0 || \
	info->time_to_eat < 0 || info->time_to_sleep < 0 || \
	info->eat_count < 0)
		return (-1);
	return (0);
}
