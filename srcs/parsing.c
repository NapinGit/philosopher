#include "../include/philosopher.h"

void	ft_bzero(void *s, size_t n)
{
	int		c;
	size_t	i;

	i = 0;
	c = 0;
	while (i < n)
	{
		((unsigned char*)s)[i] = (unsigned char)c;
		i++;
	}
}

long		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = ((result * 10) + (str[i] - '0'));
		i++;
	}
	return (result * sign);
}

int parse_int(char **av)
{
    int i;
    int k;

    k = 1;
    i = 0;
    while (av[k])
    {
        while (av[k][i])
        {
            if (av[k][i] < '0' || av[k][i] > '9')
            {
                //printf("char c = %c\n", av[k][i]);
                return (0);
            }
            i++;
        }
        i = 0;
        k++;
    }
    return (1);
}

void get_param(t_obj *obj, char **av, int ac)
{
    obj->param.nb_philo = ft_atoi(av[1]);
    obj->param.time_to_die = ft_atoi(av[2]);
    obj->param.time_to_eat = ft_atoi(av[3]);
    obj->param.time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        obj->param.nb_philo_eat = ft_atoi(av[5]);
    else
        obj->param.nb_philo_eat = -1;
}