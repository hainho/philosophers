#include "../include/philo.h"

int	free_all(t_info *info, int return_value)
{
	if (info->mutexes)
		free(info->mutexes);
	if (info->philos)
		free(info->philos);
	return (return_value);
}