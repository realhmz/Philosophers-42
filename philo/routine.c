/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:59:44 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/28 23:21:57 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sleeping(t_philo *philo)
{
	if (status(philo, 0))
		return (1);
	if (status(philo, 4))
		return (1);
	ms_sleep(philo->data->t_sleep);
	if (status(philo, 3))
		return (1);
	if (philo->data->n_of_philos == 3 || philo->data->n_of_philos == 5)
		usleep(400);
	return (0);
}

int	ft_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead);
	philo->is_dead = 1;
	// printf("hnaaaaaaaa\n");
	pthread_mutex_unlock(&philo->dead);
	return (1);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->data->finished_mutex);
		if (philo->data->finished_flag)
		{
			pthread_mutex_unlock(&philo->data->finished_mutex);
			// ft_exit(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->finished_mutex);
		if (is_eating(philo) || is_sleeping(philo))
		{
			ft_exit(philo);
			return (NULL);
		}
	}
	return (philo);
}

int	status_half(t_philo *philo, int action)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->time_mutex);
	time = what_time() - philo->data->time;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  ", time);
	pthread_mutex_unlock(&philo->data->time_mutex);
	printf("%d  ", philo->id);
	if (action == 1)
		printf("is eating\n");
	if (action == 2)
		printf("Has takken a fork\n");
	if (action == 5)
		printf("Has takken a fork\n");
	if (action == 3)
		printf("is thinking\n");
	if (action == 4)
		printf("is sleeping\n");
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	status(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->flag_mutex);
	if (!philo->data->flag)
	{
		pthread_mutex_unlock(&philo->data->flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->flag_mutex);
	if (!action)
		return (0);
	return (status_half(philo, action));
}
