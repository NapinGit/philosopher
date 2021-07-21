#include "../include/philosopher.h"

static void	philo_take_fork(t_philosopher *philo)
{
	if (philo->is_dead == 1)
		return ;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (philo->is_dead == 1)
		return ;
	pthread_mutex_lock(philo->param->display);
	printf("%ld ms : philo %ld has taken a fork\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

static void	philo_eat(t_philosopher *philo)
{
	uint64_t	eat;

	if (philo->is_dead == 1)
		return ;
	eat = get_current_time() - philo->param->time_start;
	if (eat - philo->time_last_eat > philo->param->time_to_die)
	{
		philo->is_dead = 1;
		return ;
	}
	philo->time_last_eat = eat;
	pthread_mutex_lock(philo->param->display);
	printf("%ld ms : philo %ld is eating\n", philo->time_last_eat,
		philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	usleep(philo->param->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philosopher *philo)
{
	if (philo->is_dead == 1)
		return ;
	pthread_mutex_lock(philo->param->display);
	printf("%ld ms : philo %ld is sleeping\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
	usleep(philo->param->time_to_sleep * 1000);
}

static void	philo_think(t_philosopher *philo)
{
	if (philo->is_dead == 1)
		return ;
	pthread_mutex_lock(philo->param->display);
	printf("%ld ms : philo %ld is thinking\n", get_current_time()
		- philo->param->time_start, philo->philo_name);
	pthread_mutex_unlock(philo->param->display);
}

void	*philo_day(void *phil)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)phil;
	while (philo->is_dead == 0)
	{
		if (philo->param->nb_philo_eat == philo->nb_eat)
		{
			philo->done = 1;
			break ;
		}
		philo->nb_eat++;
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
}
