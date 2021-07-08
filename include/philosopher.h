#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
typedef struct		s_philosopher
{
	//size_t			nb;
	//size_t			nb_eat;
	pthread_t		*philo;
    int             philo_name;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	//pthread_mutex_t *lock_last_meal;
	//struct timeval	*time_last_meal;
	struct s_philosopher	*next;
}	                t_philosopher;

typedef  struct     s_obj
{
    long nb_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long nb_philo_eat;
    struct s_philosopher	*first;
}                   t_obj;
//thread pour chaque philo
//mutex loc and mutex unlock pour les fourchette
void    init_philo(t_obj *obj);
void	philo_take_fork(t_obj *obj, t_philosopher *philo);
void    philo_eat(t_obj *obj, t_philosopher *philo);
#endif