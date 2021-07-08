#include "../include/philosopher.h"

void    philo_take_fork(t_obj *obj, t_philosopher *philo)
{
    //printf("yolo1 = %d\n", philo->left_fork);
    printf("ret = %d\n", pthread_mutex_lock(philo->left_fork));
    printf("ret = %d\n", pthread_mutex_lock(philo->right_fork));
    //printf("ret2 = %d\n", pthread_mutex_trylock(philo->left_fork));
    //printf("yolo2 = %d\n", philo->left_fork);
    //lock le visu du terminal
    //pthread_mutex_lock(philo->next->left_fork);
}

void    philo_eat(t_obj *obj, t_philosopher *philo)
{
    //pthread_mutex_lock(s->philo->m_display);
	//display_manager(s, philo, EVENT_EAT);
	//philo->last_meal = get_time(s->data->t_start_usec, s->data->t_start_sec);
	//pthread_mutex_unlock(s->philo->m_display);
    printf("philo start eating\n");
	usleep(obj->time_to_eat * 1);
    printf("philo finished eating\n");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}