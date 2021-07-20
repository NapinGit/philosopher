#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
//# include <iostream.h>
# include <stdint.h>
typedef struct		s_param
{
    uint64_t				nb_philo;
    uint64_t				time_to_die;
    uint64_t				time_to_eat;
    uint64_t				time_to_sleep;
    uint64_t				nb_philo_eat;
	uint64_t				time_start;
	pthread_mutex_t		*display;
	struct s_philosopher	*next;
}	                t_param;

typedef struct		s_philosopher
{
	//size_t			nb;
	//size_t			nb_eat;
	pthread_t				philo;
    uint64_t             	philo_name;
	uint64_t				time_last_eat;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	int						is_dead;
	//pthread_mutex_t *lock_last_meal;
	//struct timeval	*time_last_meal;
	struct s_param			*param;
	struct s_philosopher	*next;
}	                t_philosopher;

typedef struct     s_obj
{
    //long					nb_philo;
    //long					time_to_die;
    //long					time_to_eat;
    //long					time_to_sleep;
    //long					nb_philo_eat;
	//pthread_mutex_t			*display;
	struct s_param			param;
    struct s_philosopher	*first;
}                   t_obj;
//thread pour chaque philo
//mutex loc and mutex unlock pour les fourchette
void	ft_bzero(void *s, size_t n);
long	ft_atoi(const char *str);
int		parse_int(char **av);
void	get_param(t_obj *obj, char **av, int ac);
int    init_philo(t_obj *obj);
void	philo_take_fork(t_philosopher *philo);
void    philo_eat(t_philosopher *philo);
void    philo_sleep(t_philosopher *philo);
void    philo_think(t_philosopher *philo);
uint64_t    get_current_time(void);
#endif