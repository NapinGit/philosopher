/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:20:36 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:20:36 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	start_thread(t_obj *obj)
{
	t_philosopher	*tmp;
	long long		nb_philo;
	long long		i;

	i = 0;
	nb_philo = obj->param.nb_philo;
	obj->param.time_start = get_current_time();
	tmp = obj->first;
	while (i < nb_philo)
	{
		pthread_create(&tmp->philo, NULL, &philo_day, tmp);
		//pthread_detach(tmp->philo);
		if (tmp->next)
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		i = i + 2;
	}
	start_thread2(obj, nb_philo);
}

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
	while (tmp && tmp->done == 1)
	{
		tmp = tmp->next;
	}
	if (tmp && tmp->done == 0)
		return (1);
	return (0);
}

void	all_dead(t_obj *obj)
{
	t_philosopher	*tmp;

	tmp = obj->first;
	while(tmp)
	{
		pthread_mutex_lock(tmp->stop);
		tmp->is_dead = 1;
		pthread_mutex_unlock(tmp->stop);
		tmp = tmp->next;
	}
}

int	monitor(t_obj *obj)
{
	t_philosopher	*tmp;
	long long nb_philo_eat;

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
				pthread_mutex_unlock(tmp->stop);
				all_dead(obj);
				//pthread_mutex_lock(tmp->stop);
				//obj->param.dead_or_not = 1;
				//pthread_mutex_unlock(tmp->stop);
				stop_all_thread(obj, tmp);
				return (0);
			}
			else if (tmp->nb_eat == nb_philo_eat)
			{
				pthread_mutex_unlock(tmp->stop);
				if (check_all_stopped(obj) == 0)
				{
					pthread_mutex_lock(obj->param.display);
					
					return (0);
				}
			}
			pthread_mutex_unlock(tmp->stop);
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
		start_thread(&obj);
		monitor(&obj);
		usleep(100000);
		free_all_philo(&obj);
		//pthread_mutex_unlock(obj.param.display);
		pthread_mutex_destroy(obj.param.display);
		pthread_mutex_destroy(obj.param.stop);
		free(obj.param.display);
		free(obj.param.stop);
	}
	return (0);
}
