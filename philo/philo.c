/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:55:53 by realhmz           #+#    #+#             */
/*   Updated: 2024/08/21 19:28:11 by het-taja         ###   ########.fr       */
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
		param->cycle = 0;
		param->is_dead = 0;
		param->last_eat = what_time();
		if (pthread_create(&param->philo,NULL, &routine, (void *)param) != 0)
		{
			printf("ERROR\n");
			return (1);
		}
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
	while (i < param->data->n_of_philos)
	{
		if (pthread_mutex_init(&param->fork, NULL) != 0)
			{
				printf("ERROR\n");
				return (1);
			}
		param = param->right;
		i++;
	}
	pthread_mutex_init(&param->data->print, NULL);
	pthread_mutex_init(&param->data->time_mutex, NULL);
	pthread_mutex_init(&param->data->flag_mutex, NULL);
	pthread_mutex_init(&param->data->finished_mutex, NULL);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	if (status(philo, 0))
		return (1);
	if (status(philo, 4))
		return (1);
	ms_sleep(philo->data->t_sleep);
	if (status(philo, 3))
		return (1);
	if (philo->data->n_of_philos == 3)
		usleep(500);
	return (0);
}

int	ft_exit(t_philo *philo)
{
	int	i;

	i = 0;
	// if (philo->data->n_of_philos == 1)
	// {
	pthread_mutex_lock(&philo->data->flag_mutex);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->data->flag_mutex);
	pthread_detach(philo->philo);
	// 	return (1);
	// }
	
	// while (i <= philo->data->n_of_philos)
	// {
	// 	pthread_detach(philo->philo);
	// 	philo = philo->right;
	// 	i++;
	// }
	return (1);
}

void	*routine(void *param)
{
	t_philo *data;
	data = (t_philo *)param;
	
	// if (data->data->n_of_philos == 1)
	// 	ms_sleep(data->data->t_die);
	 if (data->id % 2 == 0)
	 	usleep(500);
		// ms_sleep(20);
	while (1)
	{
		pthread_mutex_lock(&data->data->finished_mutex);
		if (data->data->finished_flag)
		{
			pthread_mutex_unlock(&data->data->finished_mutex);
			// ft_exit(data);
			return (1);
		}
		pthread_mutex_unlock(&data->data->finished_mutex);
		if (is_eating(data))
		{
			// ft_exit(data);
			return (NULL);
		}
		else if (is_sleeping(data))
		{
			// ft_exit(data);
			return(NULL);
		}
		// printf("in\n");
	}
	
	return(data);
}