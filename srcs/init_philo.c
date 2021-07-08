#include "../include/philosopher.h"

t_philosopher	*ft_philo_new(int nb)
{
	t_philosopher	*lst;

	lst = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (lst == NULL)
		return (NULL);
	lst->next = NULL;
    lst->philo_name = nb;
	return (lst);
}

void	ft_philo_add_back(t_philosopher **list, t_philosopher *new)
{
	t_philosopher	*tmp;

	if ((*list) && new && list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
	{
		tmp = *list;
		*list = new;
	}
}

void    init_mutex_fork(t_obj *obj)
{
    int i;
    t_philosopher   *tmp;

	i = 0;
    tmp = obj->first;
	while (i < obj->nb_philo)
	{
		tmp->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (tmp->left_fork == NULL)
			return ;
		pthread_mutex_init(tmp->left_fork, NULL);
        tmp = tmp->next;
		i++;
	}
    //la partie en dessous nécesite d'etre testé pour savoir si les fork sont bien attaché les unes au autres
    i = 0;
    tmp = obj->first;
    while (i < obj->nb_philo)
    {
        if (tmp->next)
        {
            tmp->right_fork = tmp->next->left_fork;
            tmp = tmp->next;
        }
        i++;
    }
    tmp->right_fork = obj->first->left_fork;
}

void    init_philo(t_obj *obj)
{
    int number;

    number = 0;
    if (number < obj->nb_philo)
    {
        obj->first = ft_philo_new(number + 1);
        number++;
        while (number < obj->nb_philo)
        {
            ft_philo_add_back(&obj->first, ft_philo_new(number + 1));
            number++;
        }
        init_mutex_fork(obj);
    }
}