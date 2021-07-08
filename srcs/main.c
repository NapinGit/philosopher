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
    obj->nb_philo = ft_atoi(av[1]);
    obj->time_to_die = ft_atoi(av[2]);
    obj->time_to_eat = ft_atoi(av[3]);
    obj->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        obj->nb_philo_eat = ft_atoi(av[5]);
    else
        obj->nb_philo_eat = -1;
}

static void	free_all_philo(t_obj *obj)
{
	t_philosopher	*tmp;
	t_philosopher	*before;

	before = obj->first;
	tmp = NULL;
	if (before == NULL)
		return ;
	if (before->next)
		tmp = before->next;
    //destroy et free les mutex
	while (tmp)
	{
        pthread_mutex_destroy(before->left_fork);
        free(before->left_fork);
		free(before);
		before = tmp;
		tmp = before->next;
	}
    pthread_mutex_destroy(before->left_fork);
    free(before->left_fork);
	free(before);
	free(tmp);
}

int     main(int ac, char **av)
{
    t_obj obj;
    t_philosopher *tmp;

    ft_bzero(&obj, sizeof(t_obj));
    if (ac == 5 || ac == 6)
    {
        if (parse_int(av) == 0)
            return 0;
        get_param(&obj, av, ac);
        printf (" nb philospher = %ld \n time to die = %ld \n time to eat = %ld \n time to sleep = %ld \n number_of_times_each_philosopher_must_eat = %ld\n", obj.nb_philo, obj.time_to_die, obj.time_to_eat, obj.time_to_sleep, obj.nb_philo_eat);
            init_philo(&obj);
        tmp = obj.first;
        while (tmp->next)
        {
            printf("number = %d\n", tmp->philo_name);
            tmp = tmp->next;
        }
        printf("number = %d\n", tmp->philo_name);
        philo_take_fork(&obj, obj.first);
        philo_take_fork(&obj, obj.first->next);
        philo_eat(&obj, obj.first);
        free_all_philo(&obj);
    }
    return(0);
}