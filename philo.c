/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:55:53 by realhmz           #+#    #+#             */
/*   Updated: 2024/07/16 21:45:56 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int philosophers(t_philo *param)
{
	if (create_list(param) != 0)
		return (-1);
	if (create_mutex(param) != 0)
		return (-1);
	if (create_threads(param) != 0)
		return (-1);
	
	
	return (0);
}

int	create_list(t_philo *philo)
{
	t_philo	*tmp;
	t_philo *last;
	int		i;

	i = 1;
	philo->id = 1;
	tmp = philo;
	last = philo;
	while (i < philo->data.n_of_philos)
	{
		ft_lst_add_back(tmp, ft_lstnew(&philo->data), i + 1);
		i++;
		tmp = tmp->right;
		tmp->left =last;
		last = last->right;
	}
	philo->left = tmp;
	tmp->right = philo;	
	return (0);
}
int create_threads(t_philo *param)
{
    int	i;

	i = 0;
	while (i < param->data.n_of_philos)
	{
		param->taken = 0;
		if (pthread_create(&param->philo,NULL, &routine, (void *)param) != 0)
		{
			printf("ERROR\n");
			return (1);
		}
		param->data.last_meal = what_time();
		pthread_detach(param->philo);
		param = param->right;
		i++;
	}
		// pthread_join(param->philo, NULL);
	return (0);
}

int	create_mutex(t_philo *param)
{
	int	i;

	i = 0;
	while (i < param->data.n_of_philos)
	{
		if (pthread_mutex_init(&param->fork, NULL) != 0)
			{
				printf("ERROR\n");
				return (1);
			}
		pthread_mutex_init(&param->data.print,NULL);
		pthread_mutex_init(&param->cycle_mutex,NULL);
		pthread_mutex_init(&param->last_meal_mutex,NULL);
		param = param->right;
		i++;
	}
	return (0);
}

void	*routine(void *param)
{
	t_philo *data;
	data = (t_philo *)param;
	
	static long l;
	// long i = 0;
	// printf("time is %ld\n", what_time());
		if (data->id % 2 == 0)
			ms_sleep(100);

	while (1)
	{
		// printf("id :  %d, taken  %d , \n",data->id, data->taken);
		// drop_it(data);
		is_eating(data);
		ms_sleep(200);
	}
	
	return(data);
}