#include "../include/philosopher.h"

void    philo_take_fork(t_philosopher *philo)
{
    //printf("yolo1 = %d\n", philo->left_fork);
    pthread_mutex_lock(philo->param->display);
    printf("philo %d taken a fork\n", philo->philo_name);
    pthread_mutex_unlock(philo->param->display);
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    //printf("ret2 = %d\n", pthread_mutex_trylock(philo->left_fork));
    //printf("yolo2 = %d\n", philo->left_fork);
    //lock le visu du terminal
    //pthread_mutex_lock(philo->next->left_fork);
}

void    philo_eat(t_philosopher *philo)
{
    pthread_mutex_lock(philo->param->display);
    printf("philo %d start eating\n", philo->philo_name);
    pthread_mutex_unlock(philo->param->display);
	//display_manager(s, philo, EVENT_EAT);
	//philo->last_meal = get_time(s->data->t_start_usec, s->data->t_start_sec);
	//pthread_mutex_unlock(s->philo->m_display);
	usleep(philo->param->time_to_eat * 1);
    pthread_mutex_lock(philo->param->display);
    printf("philo %d finished eating\n", philo->philo_name);
    pthread_mutex_unlock(philo->param->display);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void    philo_sleep(t_philosopher *philo)
{
    pthread_mutex_lock(philo->param->display);
    printf("philo %d start sleeping\n", philo->philo_name);
    pthread_mutex_unlock(philo->param->display);
    usleep(philo->param->time_to_sleep * 1);
}

void    philo_think(t_philosopher *philo)
{
    pthread_mutex_lock(philo->param->display);
    printf("philo %d start thinking\n", philo->philo_name);
    pthread_mutex_unlock(philo->param->display);
}