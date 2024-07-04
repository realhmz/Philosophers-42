/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:24:57 by reahmz            #+#    #+#             */
/*   Updated: 2024/07/04 21:23:30 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    what_time()
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 100 + time.tv_usec / 1000);
}

void    ms_sleep(int time)
{
    long    start;

    start = what_time();
    while (what_time() - start < time)
        usleep(100);
}

void    ft_lst_add_back(t_philo *philo, t_philo *new, int id)
{
	t_philo	*head;

	head = philo;
    new->id = id;
	if (!head)
	{
		head = new;
		return ;
	}
	while (head)
	{
		if (head->right)
        {
			head = head->right;
        }
		else
		{
			head->right = new;
			return;
		}
	}    
}
// void    fill_data(t_philo *philo)
// {
    
// }

t_philo	*ft_lstnew(t_philo_data *data)
{
	t_philo	*head;

	head = (t_philo *)malloc(sizeof(t_philo));
	if (!head) 
		return (NULL);
	head->data.n_of_philos = data->n_of_philos;
	head->data.t_die = data->t_die;
	head->data.t_eat = data->t_eat;
	head->data.t_must_eat = data->t_must_eat;
	head->data.t_sleep = data->t_sleep;
	head->data.must_flag = data->must_flag;
	head->data.time = data->time;
	head->data.last_meal = data->last_meal;
    
	head->right = NULL;
	return (head);
}
void    take_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork);
    status(philo,2);
    if (philo->data.n_of_philos == 1)
        ms_sleep(philo->data.t_die);
    pthread_mutex_lock(&philo->left->fork);
    status(philo,2);
}
void    print_data(t_philo_data data)
{
    printf("n of philo %d \n",data.n_of_philos);
    printf("t_die %ld \n",data.t_die);
    printf("t_eat %ld \n",data.t_eat);
    printf("sleep %ld \n",data.t_sleep);
    printf("must eat %ld \n",data.t_must_eat);
    printf("last meal %ld \n",data.last_meal);
    printf("time %ld \n",data.time);
    printf("---------------\n\n Next Data");
}


