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
