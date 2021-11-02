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

static void	philo_take_fork_2(t_philosopher *philo)
{
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : philo %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

static void	philo_take_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	philo_take_fork_2(philo);
}

static void	philo_eat_2(t_philosopher *philo)
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
	printf("%llu ms : philo %llu is eating\n", philo->time_last_eat,
		philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	ft_usleep(philo->param->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_eat(t_philosopher *philo)
{
	long long	eat;

	eat = get_current_time() - philo->param->time_start;
	if (eat - philo->time_last_eat > philo->param->time_to_die)
	{
		pthread_mutex_lock(philo->stop);
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->stop);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	philo->time_last_eat = eat;
	philo_eat_2(philo);
}

static void	philo_sleep(t_philosopher *philo)
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
	ft_usleep(philo->param->time_to_sleep);
}

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
		pthread_mutex_lock(philo->stop);
		if (philo->is_dead == 1)
			break ;
		pthread_mutex_unlock(philo->stop);
		philo_eat(philo);
		pthread_mutex_lock(philo->stop);
		if (philo->is_dead == 1)
			break ;
		pthread_mutex_unlock(philo->stop);
		philo_sleep(philo);
		/*pthread_mutex_lock(philo->stop);
		if (philo->is_dead == 1)
			break ;
		pthread_mutex_unlock(philo->stop);*/
		philo_think(philo);
	}
	pthread_mutex_unlock(philo->stop);
	return ;
}
