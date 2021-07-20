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
	while (tmp)
	{
        if (before->left_fork != NULL)
        {
            pthread_mutex_destroy(before->left_fork);
            free(before->left_fork);
        }
		free(before);
		before = tmp;
		tmp = before->next;
	}
    if (before->left_fork != NULL)
    {
        pthread_mutex_destroy(before->left_fork);
        free(before->left_fork);
    }
	free(before);
	free(tmp);
}

void *philo_day(void *phil)
{
    t_philosopher *philo;
    philo = (t_philosopher *)phil;

    while (philo->is_dead == 0)
    {    
        if (philo->param->nb_philo_eat == philo->nb_eat)
        {
            philo->done = 1;
            break;
        }
        philo->nb_eat++;
        philo_take_fork(philo);
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);

    }
    return ((void *)0);
}


static void start_thread(t_obj  *obj)
{
    t_philosopher *tmp;

    obj->param.time_start = get_current_time();
    tmp = obj->first;
    while (tmp)
    {
        pthread_create(&tmp->philo, NULL, &philo_day, tmp);
        tmp = tmp->next;
        usleep(100);
    }
}

void    stop_all_thread(t_obj *obj)
{
    t_philosopher *tmp;

    tmp = obj->first;
    while(tmp)
    {
        tmp->is_dead = 1;
        tmp = tmp->next;
    }
}

int     check_all_stopped(t_obj *obj)
{
    t_philosopher *tmp;

    tmp = obj->first;
    while(tmp && tmp->done == 1)
    {
        tmp = tmp->next;
    }
    if (tmp && tmp->done == 0)
        return 1 ;
    return 0;
}

int     monitor(t_obj *obj)
{
    t_philosopher *tmp;
    while (1)
    {
        tmp = obj->first;
        while (tmp)
        {
            if (tmp->is_dead == 1)
            {
                pthread_mutex_lock(obj->param.display);
                printf("%ld ms : philo %ld is dead\n",get_current_time()- tmp->param->time_start, tmp->philo_name);
                stop_all_thread(obj);
                return (0);
            }
            else if (tmp->nb_eat == obj->param.nb_philo_eat)
            {
                if (check_all_stopped(obj) == 0)
                {
                    pthread_mutex_lock(obj->param.display);
                    return (0);
                }
            }
            tmp = tmp->next;
        }
    }
    return (0);
}

int     main(int ac, char **av)
{
    t_obj obj;

    ft_bzero(&obj, sizeof(t_obj));
    if (ac == 5 || ac == 6)
    {
        if (parse_int(av) == 0)
            return 0;
        if (get_param(&obj, av, ac) == 0)
            return (0);
        printf (" nb philospher = %ld \n time to die = %ld \n time to eat = %ld \n time to sleep = %ld \n number_of_times_each_philosopher_must_eat = %ld\n", obj.param.nb_philo, obj.param.time_to_die, obj.param.time_to_eat, obj.param.time_to_sleep, obj.param.nb_philo_eat);
        if (init_philo(&obj) == 0)
            return (0);
        start_thread(&obj);
        monitor(&obj);
        free_all_philo(&obj);
        pthread_mutex_destroy(obj.param.display);
        free(obj.param.display);
    }
    return(0);
}