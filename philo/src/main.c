/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iha <iha@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:14:03 by iha               #+#    #+#             */
/*   Updated: 2022/03/15 23:14:04 by iha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (init(&info, argc, argv) == -1)
		return (free_all(&info, -1));
	if (philo_run(&info) == -1)
		return (free_all(&info, -1));
	philo_death_check(&info);
	philo_end(&info);
	return (free_all(&info, 0));
}
