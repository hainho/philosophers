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
