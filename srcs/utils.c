#include "../include/philosopher.h"


uint64_t    get_current_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	free_all_philo(t_obj *obj)
{
	t_philosopher	*tmp;
	t_philosopher	*before;

	before = obj->first;
	tmp = NULL;
	if (before == NULL)
		return ;
	if (before->next)
		tmp = before->next;
	while (tmp)
	{
        if (before->left_fork != NULL)
        {
            pthread_mutex_destroy(before->left_fork);
            free(before->left_fork);
        }
		free(before);
		before = tmp;
		tmp = before->next;
	}
    if (before->left_fork != NULL)
    {
        pthread_mutex_destroy(before->left_fork);
        free(before->left_fork);
    }
	free(before);
	free(tmp);
}