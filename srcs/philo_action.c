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

static void	philo_take_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->param->dead_or_not == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	if (philo->param->dead_or_not == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->param->display);
	if (philo->param->dead_or_not == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->param->display);
		return ;
	}
	printf("%llu ms : philo %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

static void	philo_eat(t_philosopher *philo)
{
	long long	eat;

	eat = get_current_time() - philo->param->time_start;
	if (eat - philo->time_last_eat > philo->param->time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	philo->time_last_eat = eat;
	pthread_mutex_lock(philo->param->display);
	if (philo->param->dead_or_not == 1)
	{
		pthread_mutex_unlock(philo->param->display);
		return ;
	}
	printf("%llu ms : philo %llu is eating\n", philo->time_last_eat,
		philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	ft_usleep(philo->param->time_to_eat, philo->param);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->display);
	if (philo->param->dead_or_not == 1)
	{
		pthread_mutex_unlock(philo->param->display);
		return ;
	}
	printf("%llu ms : philo %llu is sleeping\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	ft_usleep(philo->param->time_to_sleep, philo->param);
}

static void	philo_think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->display);
	if (philo->param->dead_or_not == 1)
	{
		pthread_mutex_unlock(philo->param->display);
		return ;
	}
	printf("%llu ms : philo %llu is thinking\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

void	philo_day2(t_philosopher *philo)
{
	while (philo->param->dead_or_not == 0)
	{
		if (philo->param->nb_philo_eat == philo->nb_eat)
		{
			philo->done = 1;
			break ;
		}
		philo->nb_eat++;
		if (philo->param->dead_or_not == 1)
			break ;
		philo_take_fork(philo);
		if (philo->param->dead_or_not == 1)
			break ;
		philo_eat(philo);
		if (philo->param->dead_or_not == 1)
			break ;
		philo_sleep(philo);
		if (philo->param->dead_or_not == 1)
			break ;
		philo_think(philo);
	}
	return ;
}
