/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <aloiseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:21:07 by aloiseau          #+#    #+#             */
/*   Updated: 2021/09/09 11:21:07 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_param
{
	long long				nb_philo;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				nb_philo_eat;
	long long				time_start;
	pthread_mutex_t			*display;
	pthread_mutex_t			*stop;
	int						dead_or_not;
	struct s_philosopher	*next;
}							t_param;

typedef struct s_philosopher
{
	long long				nb_eat;
	pthread_t				philo;
	long long				philo_name;
	long long				time_last_eat;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	int						is_dead;
	int						done;
	struct s_param			*param;
	struct s_philosopher	*next;
	pthread_mutex_t			*stop;
}							t_philosopher;

typedef struct s_obj
{
	struct s_param			param;
	struct s_philosopher	*first;
}							t_obj;

void		ft_bzero(void *s, size_t n);
long		ft_atoi(const char *str);
int			parse_int(char **av);
int			get_param(t_obj *obj, char **av, int ac);
int			init_philo(t_obj *obj);
void		*philo_day(void *phil);
long long	get_current_time(void);
void		start_thread2(t_obj *obj, long long nb_philo);
void		free_all_philo(t_obj *obj);
void		philo_day2(t_philosopher *philo, long long nb_philo_eat);
void		ft_usleep(long long time);
int	monitor(t_obj *obj);
#endif
