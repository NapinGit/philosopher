/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:20:56 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:20:56 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long long	get_current_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000));
}

static void	destroy_fork(t_philosopher	*before)
{
	pthread_mutex_destroy(before->left_fork);
	pthread_mutex_destroy(before->stop);
	free(before->left_fork);
	free(before->stop);
}

void	*philo_day(void *phil)
{
	t_philosopher	*philo;
	long long		nb_philo_eat;
	long long		nb_philo;

	philo = (t_philosopher *)phil;
	pthread_mutex_lock(philo->param->stop);
	nb_philo = philo->param->nb_philo;
	nb_philo_eat = philo->param->nb_philo_eat;
	pthread_mutex_unlock(philo->param->stop);
	if (nb_philo == 1)
	{
		printf("%llu ms : philo %llu has taken a fork\n", get_current_time()
			- philo->param->time_start, philo->philo_name);
		pthread_mutex_lock(philo->left_fork);
		usleep(philo->param->time_to_die * 1000);
		pthread_mutex_lock(philo->stop);
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->stop);
		pthread_mutex_unlock(philo->left_fork);
		return ((void *)0);
	}
	philo_day2(philo, nb_philo_eat);
	return ((void *)0);
}

void	free_all_philo(t_obj *obj)
{
	t_philosopher	*tmp;
	t_philosopher	*before;

	before = obj->first;
	tmp = NULL;
	if (before == NULL)
		return ;
	if (before->next)
		tmp = before->next;
	while (tmp)
	{
		if (before->left_fork != NULL)
			destroy_fork(before);
		free(before);
		before = tmp;
		tmp = before->next;
	}
	if (before->left_fork != NULL)
	{
		destroy_fork(before);
	}
	free(before);
	free(tmp);
}

t_philosopher	*ft_philo_new(int nb)
{
	t_philosopher	*lst;

	lst = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (lst == NULL)
		return (NULL);
	lst->next = NULL;
	lst->philo_name = nb;
	lst->is_dead = 0;
	lst->time_last_eat = 0;
	lst->nb_eat = 0;
	lst->done = 0;
	return (lst);
}
