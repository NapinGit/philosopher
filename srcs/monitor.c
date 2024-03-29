/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:20:56 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:20:56 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	stop_all_thread(t_obj *obj, t_philosopher *die)
{
	t_philosopher	*tmp;

	tmp = obj->first;
	pthread_mutex_lock(obj->param.display);
	printf("%llu ms : %llu is dead\n", get_current_time()
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

void	all_dead(t_obj *obj, t_philosopher *stop)
{
	t_philosopher	*tmp;

	pthread_mutex_unlock(stop->stop);
	tmp = obj->first;
	while (tmp)
	{
		pthread_mutex_lock(tmp->stop);
		tmp->is_dead = 1;
		pthread_mutex_unlock(tmp->stop);
		tmp = tmp->next;
	}
}

int	monitor_2(t_obj *obj, t_philosopher *tmp)
{
	all_dead(obj, tmp);
	stop_all_thread(obj, tmp);
	return (0);
}

int	monitor_3(t_obj *obj, t_philosopher *tmp)
{
	pthread_mutex_unlock(tmp->stop);
	if (check_all_stopped(obj) == 0)
	{
		join_when_eat(obj);
		return (0);
	}
	return (1);
}
