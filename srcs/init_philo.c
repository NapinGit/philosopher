/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:20:19 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:20:19 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_philo_add_back(t_philosopher **list, t_philosopher *new)
{
	t_philosopher	*tmp;

	if ((*list) && new && list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
	{
		tmp = *list;
		*list = new;
	}
}

void	set_fork(t_obj *obj)
{
	long long		i;
	t_philosopher	*tmp;

	i = 0;
	tmp = obj->first;
	while (i < obj->param.nb_philo)
	{
		tmp->param = &obj->param;
		if (tmp->next)
		{
			tmp->right_fork = tmp->next->left_fork;
			tmp = tmp->next;
		}
		i++;
	}
	tmp->param = &obj->param;
	tmp->right_fork = obj->first->left_fork;
}

int	init_mutex_fork(t_obj *obj)
{
	long long		i;
	t_philosopher	*tmp;

	i = 0;
	tmp = obj->first;
	while (i < obj->param.nb_philo)
	{
		tmp->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (tmp->left_fork == NULL)
			return (0);
		if (pthread_mutex_init(tmp->left_fork, NULL))
			return (0);
		tmp->stop = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (tmp->stop == NULL)
			return (0);
		if (pthread_mutex_init(tmp->stop, NULL))
			return (0);
		tmp = tmp->next;
		i++;
	}
	set_fork(obj);
	return (1);
}

int	create_mutex(t_obj *obj)
{
	obj->param.display = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (obj->param.display == NULL)
		return (0);
	obj->param.stop = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (obj->param.stop == NULL)
		return (0);
	if (pthread_mutex_init(obj->param.stop, NULL))
		return (0);
	if (pthread_mutex_init(obj->param.display, NULL))
		return (0);
	return (1);
}

int	init_philo(t_obj *obj)
{
	long long	number;

	number = 0;
	if (number < obj->param.nb_philo)
	{
		obj->first = ft_philo_new(number + 1);
		number++;
		while (number < obj->param.nb_philo)
		{
			ft_philo_add_back(&obj->first, ft_philo_new(number + 1));
			number++;
		}
		if (init_mutex_fork(obj) == 0)
			return (0);
	}
	if (create_mutex(obj) == 0)
		return (0);
	return (1);
}
