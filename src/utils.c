#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(const char c)
{
	if (c == '\t' || c == '\f' || c == '\r')
		return (1);
	else if (c == '\v' || c == '\n' || c == ' ')
		return (1);
	else
		return (0);
}

long long	ft_atol(const char *str)
{
	unsigned long long	n;
	int					sign;

	sign = 1;
	n = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
		if (n >= LLONG_MAX && sign == 1)
			return (LLONG_MIN);
		if (n > LLONG_MAX && sign == -1)
			return (LLONG_MIN);
	}
	if (*str != 0)
		return (LLONG_MIN);
	return ((long long)n * sign);
}

long long	get_cur_time()
{
	struct timeval	time;
	long long		cur_time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	cur_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (cur_time);
}

int	print_philo_state(t_info *info, t_philo *philo, int state)
{
	long long	cur_time;

	cur_time = get_cur_time();
	if (cur_time == -1)
		return (-1);
	printf("%lld ", (cur_time - info->start_time));
	if (state == SLEEPING)
		printf("%d is sleeping", philo->idx);
	else if (state == EATING)
		printf("%d is eating", philo->idx);
	else if (state == THINKING)
		printf("%d is thinking", philo->idx);
	else if (state == TAKEFORK)
		printf("%d has take fork", philo->idx);
	else
		return (-1);
	return (0);
}