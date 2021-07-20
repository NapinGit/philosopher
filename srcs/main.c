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
    int i;

    i = 0;
     //printf("number = %ld = nb philospher = %ld \n time to die = %ld \n time to eat = %ld \n time to sleep = %ld \n number_of_times_each_philosopher_must_eat = %ld\n ||||||||||||\n", philo->philo_name, philo->param->nb_philo, philo->param->time_to_die, philo->param->time_to_eat, philo->param->time_to_sleep, philo->param->nb_philo_eat);
    while (philo->is_dead == 0)
    {
        philo_take_fork(philo);
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
        /*if (philo->param->nb_philo_eat != -1)
        {
            if (philo->param->nb_philo_eat == i)
                break;
            i++;
        }*/
    }
    return ((void *)0);
}


static void start_thread(t_obj  *obj)
{
    t_philosopher *tmp;

    tmp = obj->first;
    while (tmp->next)
    {
        printf("number = %ld \n", tmp->philo_name);
        tmp = tmp->next;
    }
    printf("number = %ld\n", tmp->philo_name);
    obj->param.time_start = get_current_time();
    tmp = obj->first;
    while (tmp)
    {
        //printf("%d\n", tmp->philo_name);
        pthread_create(&tmp->philo, NULL, &philo_day, tmp);
        //pthread_detach(tmp->philo);
        tmp = tmp->next;
        usleep(100);
    }
    
    //pthread_create(&tmp->philo, NULL, &philo_day, tmp);
    //usleep(1000);
}

void    stop_all_thread(t_obj *obj)
{
    t_philosopher *tmp;

    tmp = obj->first;
    while(tmp)
    {
        tmp->is_dead = 1;
        //pthread_join(tmp->philo, NULL);
        tmp = tmp->next;
    }
}

int     monitor(t_obj *obj)
{
    t_philosopher *tmp;
    while (1)
    {
        tmp = obj->first;
        while (tmp)
        {
            //doit tout arrété et ensuite tout free
            if (tmp->is_dead == 1)
            {
                pthread_mutex_lock(obj->param.display);
                printf("%ld : philo %ld is dead\n",get_current_time()- tmp->param->time_start, tmp->philo_name);
                //pthread_mutex_unlock(obj->param.display);
                stop_all_thread(obj);
                return (0);
            }
            tmp = tmp->next;
        }
    }
    return (0);
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
        printf (" nb philospher = %ld \n time to die = %ld \n time to eat = %ld \n time to sleep = %ld \n number_of_times_each_philosopher_must_eat = %ld\n", obj.param.nb_philo, obj.param.time_to_die, obj.param.time_to_eat, obj.param.time_to_sleep, obj.param.nb_philo_eat);
        if (init_philo(&obj) == 0)
            return (0);
        //la ligne du dessus necessitera de free si ce qui a été aloué
       /*tmp = obj.first;
        while (tmp->next)
        {
            printf("number = %ld = nb philospher = %ld \n time to die = %ld \n time to eat = %ld \n time to sleep = %ld \n number_of_times_each_philosopher_must_eat = %ld\n ||||||||||||\n", tmp->philo_name, tmp->param->nb_philo, tmp->param->time_to_die, tmp->param->time_to_eat, tmp->param->time_to_sleep, tmp->param->nb_philo_eat);
            tmp = tmp->next;
        }
        printf("number = %ld = nb philospher = %ld \n time to die = %ld \n time to eat = %ld \n time to sleep = %ld \n number_of_times_each_philosopher_must_eat = %ld\n ||||||||||||\n", tmp->philo_name, tmp->param->nb_philo, tmp->param->time_to_die, tmp->param->time_to_eat, tmp->param->time_to_sleep, tmp->param->nb_philo_eat);
        */
        start_thread(&obj);
        monitor(&obj);
        //usleep(1000000);
        //printf("yolo\n");
        //philo_take_fork(&obj, obj.first);
        //philo_take_fork(&obj, obj.first->next);
        //philo_eat(&obj, obj.first);
        free_all_philo(&obj);
    }
    return(0);
}