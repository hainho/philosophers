/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:13:48 by iha               #+#    #+#             */
/*   Updated: 2022/03/15 23:13:49 by iha              ###   ########.fr       */
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
