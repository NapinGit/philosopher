/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:20:26 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:20:26 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	philo_think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : philo %llu is thinking\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

void	philo_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : philo %llu is sleeping\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	ft_usleep(philo->param->time_to_sleep, philo->param->time_start);
	//usleep(philo->param->time_to_sleep * 1000);
	philo_think(philo);
}

int	philo_day_end(t_philosopher *philo)
{
	pthread_mutex_lock(philo->stop);
	philo->done = 1;
	pthread_mutex_unlock(philo->stop);
	return (0);
}

void	philo_day2(t_philosopher *philo, long long nb_philo_eat)
{
	while (1)
	{
		if (nb_philo_eat == philo->nb_eat)
			if (philo_day_end(philo) == 0)
				return ;
		pthread_mutex_lock(philo->stop);
		philo->nb_eat++;
		if (philo->is_dead == 1)
			break ;
		pthread_mutex_unlock(philo->stop);
		philo_take_fork(philo);
	}
	pthread_mutex_unlock(philo->stop);
	return ;
}
