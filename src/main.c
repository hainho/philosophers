#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (init(&info, argc, argv) == -1)
		return (free_all(&info, -1));
	return (0);
}
