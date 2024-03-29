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
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	uint64_t				time_to_sleep;
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

void			ft_bzero(void *s, size_t n);
long			ft_atoi(const char *str);
int				parse_int(char **av);
int				get_param(t_obj *obj, char **av, int ac);
int				init_philo(t_obj *obj);
void			*philo_day(void *phil);
long long		get_current_time(void);
void			free_all_philo(t_obj *obj);
void			philo_day2(t_philosopher *philo, long long nb_philo_eat);
void			ft_usleep(uint64_t time, uint64_t time_start);
int				monitor_2(t_obj *obj, t_philosopher *tmp);
int				monitor_3(t_obj *obj, t_philosopher *tmp);
void			join_when_eat(t_obj *obj);
void			philo_take_fork(t_philosopher *philo);
t_philosopher	*ft_philo_new(int nb);
void			philo_sleep(t_philosopher *philo);
void			philo_eat(t_philosopher *philo);
#endif
