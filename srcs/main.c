/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:20:36 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:20:36 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	start_thread(t_obj *obj)
{
	t_philosopher	*tmp;
	long long		nb_philo;
	long long		i;

	i = 0;
	nb_philo = obj->param.nb_philo;
	obj->param.time_start = get_current_time();
	tmp = obj->first;
	while (i < nb_philo)
	{
		pthread_create(&tmp->philo, NULL, &philo_day, tmp);
		if (tmp->next)
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		i = i + 2;
	}
	start_thread2(obj, nb_philo);
}

int	main(int ac, char **av)
{
	t_obj	obj;

	ft_bzero(&obj, sizeof(t_obj));
	if (ac == 5 || ac == 6)
	{
		if (parse_int(av) == 0)
			return (0);
		if (get_param(&obj, av, ac) == 0)
			return (0);
		if (init_philo(&obj) == 0)
			return (0);
		start_thread(&obj);
		monitor(&obj);
		usleep(100000);
		free_all_philo(&obj);
		pthread_mutex_destroy(obj.param.display);
		pthread_mutex_destroy(obj.param.stop);
		free(obj.param.display);
		free(obj.param.stop);
	}
	return (0);
}
