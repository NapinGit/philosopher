#include "../include/philosopher.h"

void	stop_all_thread(t_obj *obj, t_philosopher *die)
{
	t_philosopher	*tmp;

	tmp = obj->first;
	pthread_mutex_lock(obj->param.display);
	printf("%llu ms : philo %llu is dead\n", get_current_time()
		- tmp->param->time_start, die->philo_name);
	pthread_mutex_unlock(obj->param.display);
	while (tmp)
	{
		pthread_join(tmp->philo, NULL);
		tmp = tmp->next;
	}
}

int	check_all_stopped(t_obj *obj)
{
	t_philosopher	*tmp;

	tmp = obj->first;
    pthread_mutex_unlock(tmp->stop);
	while (tmp)
	{
		pthread_mutex_lock(tmp->stop);
		if (tmp->done == 0)
		{
			pthread_mutex_unlock(tmp->stop);
			break ;
		}
		pthread_mutex_unlock(tmp->stop);
		tmp = tmp->next;
	}
	if (tmp)
	{
		pthread_mutex_lock(tmp->stop);
		if (tmp && tmp->done == 0)
		{
			pthread_mutex_unlock(tmp->stop);
			return (1);
		}
		pthread_mutex_unlock(tmp->stop);
	}
	return (0);
}

void	all_dead(t_obj *obj)
{
	t_philosopher	*tmp;

	tmp = obj->first;
    pthread_mutex_unlock(tmp->stop);
	while (tmp)
	{
		pthread_mutex_lock(tmp->stop);
		tmp->is_dead = 1;
		pthread_mutex_unlock(tmp->stop);
		tmp = tmp->next;
	}
    stop_all_thread(obj, tmp);
}

void	join_when_eat(t_obj *obj)
{
	t_philosopher	*tmp;

	tmp = obj->first;
	while (tmp)
	{
		pthread_join(tmp->philo, NULL);
		tmp = tmp->next;
	}
}

int	monitor(t_obj *obj)
{
	t_philosopher	*tmp;
	long long		nb_philo_eat;

	pthread_mutex_lock(obj->param.stop);
	nb_philo_eat = obj->param.nb_philo_eat;
	pthread_mutex_unlock(obj->param.stop);
	while (1)
	{
		tmp = obj->first;
		while (tmp)
		{
			pthread_mutex_lock(tmp->stop);
			if (tmp->is_dead == 1)
			{
				all_dead(obj);
				return (0);
			}
			if (tmp->nb_eat == nb_philo_eat)
			{
				if (check_all_stopped(obj) == 0)
				{
					join_when_eat(obj);
					return (0);
				}
			}
			else
				pthread_mutex_unlock(tmp->stop);
			tmp = tmp->next;
		}
	}
	return (0);
}
