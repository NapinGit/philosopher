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

void	start_thread2(t_obj *obj, long long nb_philo)
{
	long long		i;
	t_philosopher	*tmp;

	i = 0;
	tmp = obj->first->next;
	while (i < nb_philo && tmp)
	{
		pthread_create(&tmp->philo, NULL, &philo_day, tmp);
		if (tmp->next)
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		usleep(100);
		i = i + 2;
	}
}

void	ft_usleep(uint64_t time, uint64_t time_start)
{
	uint64_t	end;

	end = get_current_time() - time_start + time;
	while (get_current_time() - time_start < end)
		usleep(10);
}
