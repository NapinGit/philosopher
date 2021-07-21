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
	uint64_t				nb_philo;
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	uint64_t				time_to_sleep;
	uint64_t				nb_philo_eat;
	uint64_t				time_start;
	pthread_mutex_t			*display;
	struct s_philosopher	*next;
}							t_param;

typedef struct s_philosopher
{
	uint64_t				nb_eat;
	pthread_t				philo;
	uint64_t				philo_name;
	uint64_t				time_last_eat;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	int						is_dead;
	int						done;
	struct s_param			*param;
	struct s_philosopher	*next;
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
uint64_t	get_current_time(void);
void		free_all_philo(t_obj *obj);
#endif
