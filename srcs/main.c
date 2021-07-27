#include "../include/philosopher.h"

static void	start_thread(t_obj *obj)
{
	t_philosopher	*tmp;

	obj->param.time_start = get_current_time();
	tmp = obj->first;
	printf("dead or not =%d\n", tmp->param->dead_or_not);
	while (tmp)
	{
		pthread_create(&tmp->philo, NULL, &philo_day, tmp);
		tmp = tmp->next;
		usleep(100);
	}
}

void	stop_all_thread(t_obj *obj, t_philosopher *die)
{
	t_philosopher	*tmp;

	tmp = obj->first;
	pthread_mutex_lock(obj->param.display);
	printf("%ld ms : philo %ld is dead\n", get_current_time()
		- tmp->param->time_start, die->philo_name);
	pthread_mutex_unlock(obj->param.display);
	while (tmp)
	{
		//tmp->is_dead = 1;
		//pthread_mutex_unlock(tmp->left_fork);
		//pthread_mutex_unlock(tmp->right_fork);
		pthread_join(tmp->philo, NULL);
		
		tmp = tmp->next;
	}
	/*pthread_mutex_lock(obj->param.display);
	printf("%ld ms : philo %ld is dead\n", get_current_time()
		- tmp->param->time_start, die->philo_name);
	pthread_mutex_unlock(obj->param.display);*/
	//pthread_mutex_unlock(obj->param.display);
}

int	check_all_stopped(t_obj *obj)
{
	t_philosopher	*tmp;

	tmp = obj->first;
	while (tmp && tmp->done == 1)
	{
		tmp = tmp->next;
	}
	if (tmp && tmp->done == 0)
		return (1);
	return (0);
}

int	monitor(t_obj *obj)
{
	t_philosopher	*tmp;

	while (1)
	{
		tmp = obj->first;
		while (tmp)
		{
			if (tmp->is_dead == 1)
			{
				obj->param.dead_or_not = 1;
				stop_all_thread(obj, tmp);
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

int	main(int ac, char **av)
{
	t_obj	obj;

	ft_bzero(&obj, sizeof(t_obj));
	if (ac == 5 || ac == 6)
	{
		if (parse_int(av) == 0)
			return (0);
		if (get_param(&obj, av, ac) == 0)
			return (0);
		if (init_philo(&obj) == 0)
			return (0);
		//t-philo

		start_thread(&obj);
		monitor(&obj);
		usleep(1000);
		free_all_philo(&obj);
		pthread_mutex_destroy(obj.param.display);
		free(obj.param.display);
	}
	return (0);
}
