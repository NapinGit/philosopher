/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:50:09 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:50:09 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	start_thread2(t_obj *obj)
{
	long long		i;
	t_philosopher	*tmp;

	i = 1;
	tmp = obj->first->next;
	while (i < obj->param.nb_philo && tmp)
	{
		pthread_create(&tmp->philo, NULL, &philo_day, tmp);
		if (tmp->next)
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		i = i + 2;
	}
}

void	ft_usleep(long long time, t_param *param)
{
	long long	i;

	i = get_current_time();
	while (param->dead_or_not == 0)
	{
		if ((get_current_time() - i) >= time)
		{
			break ;
		}
		usleep(5);
	}
}
