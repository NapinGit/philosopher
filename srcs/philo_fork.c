/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:50:09 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:50:09 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	philo_take_right_fork_2(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

static void	philo_take_right_fork(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	philo_take_right_fork_2(philo);
}

static void	philo_take_left_fork_2(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

static void	philo_take_left_fork(t_philosopher *philo)
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
	pthread_mutex_lock(philo->param->display);
	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	philo_take_left_fork_2(philo);
}

void	philo_take_fork(t_philosopher *philo)
{
	if ((philo->philo_name) % 2)
	{
		philo_take_right_fork(philo);
	}
	else
	{
		philo_take_left_fork(philo);
	}
	philo_eat(philo);
}
