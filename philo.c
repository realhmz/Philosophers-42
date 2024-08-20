/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:55:53 by realhmz           #+#    #+#             */
/*   Updated: 2024/08/20 10:41:58 by het-taja         ###   ########.fr       */
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

	philo->id = 1;
	tmp = philo;
	last = philo;
	// if (philo->data.n_of_philos % 2 != 0)
	// {
	// 	i = philo->data.n_of_philos + 1;
	// 	while (i > 0)
	// 	{
	// 		ft_lst_add_back(tmp, ft_lstnew(&philo->data), i - 1);
	// 		i--;
	// 		tmp = tmp->right;
	// 		tmp->left =last;
	// 		last = last->right;
	// 	}
	// 	philo->left = tmp;
	// 	tmp->right = philo;	
	// }
	// else
	{
		i = 1;
		while (i < philo->data->n_of_philos)
		{
			ft_lst_add_back(tmp, ft_lstnew(philo->data), i + 1);
			i++;
			tmp = tmp->right;
			tmp->left =last;
			last = last->right;
		}
		philo->left = tmp;
		tmp->right = philo;
	}
	return (0);
}
int create_threads(t_philo *param)
{
    int	i;

	i = 0;
	param->data->time = what_time();
	while (i < param->data->n_of_philos)
	{
		param->last_eat = what_time();
		if (pthread_create(&param->philo,NULL, &routine, (void *)param) != 0)
		{
			printf("ERROR\n");
			return (1);
		}
		// param->data->last_meal = what_time();
		// pthread_detach(param->philo);
		param = param->right;
		param->data = param->left->data;
		i++;
	}
		// pthread_join(param->philo, NULL);
	return (0);
}

int	create_mutex(t_philo *param)
{
	int	i;

	i = 0;
	while (i < param->data->n_of_philos)
	{
		if (pthread_mutex_init(&param->fork, NULL) != 0)
			{
				printf("ERROR\n");
				return (1);
			}
		// pthread_mutex_init(&param->taken_mtx,NULL);
		// pthread_mutex_init(&param->timer_mtx,NULL);
		// pthread_mutex_init(&param->data.print,NULL);
		// pthread_mutex_init(&param->cycle_mutex,NULL);
		// pthread_mutex_init(&param->last_meal_mutex,NULL);
		param = param->right;
		i++;
	}
	pthread_mutex_init(&param->data->print, NULL);
	pthread_mutex_init(&param->data->time_mutex, NULL);
	return (0);
}

void	is_sleeping(t_philo *philo)
{
	status(philo, 4);
	ms_sleep(philo->data->t_sleep);
	status(philo, 3);

}

int	ft_exit(t_philo *philo)
{
	pthread_join(philo->philo, NULL);
	return (1);
}

void	*routine(void *param)
{
	t_philo *data;
	data = (t_philo *)param;
	
	if (data->id % 2 != 0)
	{
		// qleb_o_chqleb(data);	
		ms_sleep(50);
	}
	while (1)
	{
		is_eating(data);
		is_sleeping(data);
		// printf("in\n");
	}
	
	return(data);
}