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
		if (tmp->next)
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		usleep(1000);
		i = i + 2;
	}
	start_thread2(obj, nb_philo);
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

int	monitor(t_obj *obj, long long nb_philo_eat)
{
	t_philosopher	*tmp;

	while (1)
	{
		tmp = obj->first;
		while (tmp)
		{
			pthread_mutex_lock(tmp->stop);
			if (tmp->is_dead == 1)
				if (monitor_2(obj, tmp) == 0)
					return (0);
			if (tmp->nb_eat == nb_philo_eat)
			{
				pthread_mutex_unlock(tmp->stop);
				if (monitor_3(obj) == 0)
					return (0);
			}
			else
				pthread_mutex_unlock(tmp->stop);
			tmp = tmp->next;
		}
		usleep(10);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_obj		obj;
	long long	nb_philo_eat;

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
		pthread_mutex_lock(obj.param.stop);
		nb_philo_eat = obj.param.nb_philo_eat;
		pthread_mutex_unlock(obj.param.stop);
		monitor(&obj, nb_philo_eat);
		usleep(1000);
		free_all_philo(&obj);
		pthread_mutex_destroy(obj.param.display);
		pthread_mutex_destroy(obj.param.stop);
		free(obj.param.display);
		free(obj.param.stop);
	}
	return (0);
}
