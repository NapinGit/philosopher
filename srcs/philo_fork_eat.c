/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_eat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:50:09 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:50:09 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	philo_eat_2(t_philosopher *philo)
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
	printf("%llu ms : %llu is eating\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	ft_usleep(philo->param->time_to_eat, philo->param->time_start);
	//usleep(philo->param->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_sleep(philo);
}

static void	philo_eat(t_philosopher *philo)
{
	uint64_t	eat;

	pthread_mutex_lock(philo->stop);
	if (philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	eat = get_current_time() - philo->param->time_start;
	philo->time_last_eat = eat;
	pthread_mutex_unlock(philo->stop);
	philo_eat_2(philo);
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
	philo_eat(philo);
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
	philo_eat(philo);
}

/*static void	philo_take_fork_2(t_philosopher *philo)
{
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
	philo_eat(philo);
}

void	philo_take_fork(t_philosopher *philo)
{
	if (philo->nb_philo + philo->nb_philo_eat) % 2
	else


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
		pthread_mutex_unlock(philo->param->display);
		pthread_mutex_unlock(philo->stop);
		return ;
	}
	pthread_mutex_unlock(philo->stop);
	printf("%llu ms : philo %llu has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	philo_take_fork_2(philo);
}*/

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
}
