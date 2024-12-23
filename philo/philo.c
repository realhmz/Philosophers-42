/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:55:53 by realhmz           #+#    #+#             */
/*   Updated: 2024/11/09 17:37:29 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(t_philo *param)
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
	t_philo	*last;
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
			tmp->left = last;
			last = last->right;
		}
		philo->left = tmp;
		tmp->right = philo;
	}
	return (0);
}

void	join_th(t_philo *param)
{
	int	i;

	i = 0;
	while (i < param->data->n_of_philos)
	{
		pthread_join(param->philo, NULL);
		param = param->right;
		i++;
	}
	pthread_join(param->data->checker, NULL);
}

int	create_threads(t_philo *param)
{
	int	i;

	i = 0;
	param->data->time = what_time();
	param->data->created = 0;
	while (i < param->data->n_of_philos)
	{
		param->cycle = 0;
		param->is_dead = 0;
		param->last_eat = param->data->time;
		if (pthread_create(&param->philo, NULL, &routine, (void *)param) != 0)
		{
			printf("ERROR\n");
			return (1);
		}
		param = param->right;
		i++;
	}
	if (pthread_create(&param->data->checker,
			NULL, &monitor_check, (void *)param) != 0)
		return (1);
	join_th(param);
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
		pthread_mutex_init(&param->dead, NULL);
		pthread_mutex_init(&param->cycle_mutex, NULL);
		pthread_mutex_init(&param->last_eat_mutex, NULL);
		param = param->right;
		i++;
	}
	pthread_mutex_init(&param->data->print, NULL);
	pthread_mutex_init(&param->data->time_mutex, NULL);
	pthread_mutex_init(&param->data->flag_mutex, NULL);
	pthread_mutex_init(&param->data->finished_mutex, NULL);
	return (0);
}
