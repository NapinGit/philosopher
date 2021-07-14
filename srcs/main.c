#include "../include/philosopher.h"

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

void *philo_day(void *phil)
{
    t_philosopher *philo;
    philo = phil;
    int i;

    i = 0;
    while (1)
    {
        //segfault au second passage de prise de fork
        //return ((void *)0);
        philo_take_fork(philo);
        //return ((void *)0);
        philo_eat(philo);
        //return ((void *)0);
        philo_sleep(philo);
        philo_think(philo);
        if (philo->param->nb_philo_eat != -1)
        {
            if (philo->param->nb_philo_eat == i)
                break;
            i++;
        }
    }
    return ((void *)0);
}


static void start_thread(t_obj  *obj)
{
    t_philosopher *tmp;

    tmp = obj->first;
    while (tmp->next)
    {
        //printf("coucou1\n");
        //printf("%d\n", tmp->philo_name);
        pthread_create(&tmp->philo, NULL, &philo_day, tmp);
        //printf("coucou2\n");
        tmp = tmp->next;
    }
    pthread_create(&tmp->philo, NULL, &philo_day, tmp);
    //printf("coucou\n");
    //printf("%d\n", tmp->philo_name);
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
        printf (" nb philospher = %d \n time to die = %d \n time to eat = %d \n time to sleep = %d \n number_of_times_each_philosopher_must_eat = %d\n", obj.param.nb_philo, obj.param.time_to_die, obj.param.time_to_eat, obj.param.time_to_sleep, obj.param.nb_philo_eat);
            init_philo(&obj);
       /* tmp = obj.first;
        while (tmp->next)
        {
            printf("number = %d = nb philospher = %d \n time to die = %d \n time to eat = %d \n time to sleep = %d \n number_of_times_each_philosopher_must_eat = %d\n ||||||||||||\n", tmp->philo_name, tmp->param->nb_philo, tmp->param->time_to_die, tmp->param->time_to_eat, tmp->param->time_to_sleep, tmp->param->nb_philo_eat);
            tmp = tmp->next;
        }
        printf("number = %d = nb philospher = %d \n time to die = %d \n time to eat = %d \n time to sleep = %d \n number_of_times_each_philosopher_must_eat = %d\n ||||||||||||\n", tmp->philo_name, tmp->param->nb_philo, tmp->param->time_to_die, tmp->param->time_to_eat, tmp->param->time_to_sleep, tmp->param->nb_philo_eat);*/
        start_thread(&obj);
        //printf("yolo\n");
        //philo_take_fork(&obj, obj.first);
        //philo_take_fork(&obj, obj.first->next);
        //philo_eat(&obj, obj.first);
        free_all_philo(&obj);
    }
    return(0);
}