/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:42:02 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/22 22:47:08 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo, int action)
{
	if (action == 0 && odd_eat(philo))
		return (1);
	else if (action && eat_even(philo))
		return (1);
	pthread_mutex_lock(&philo->cycle_mutex);
	philo->cycle++;
	pthread_mutex_unlock(&philo->cycle_mutex);
	return (0);
}

int	is_eating(t_philo *philo)
{
	if (status(philo, 0))
		return (1);
	if (philo->data->must_flag)
	{
		pthread_mutex_lock(&philo->cycle_mutex);
		if (philo->data->t_must_eat == philo->cycle - 1)
		{
			pthread_mutex_lock(&philo->data->finished_mutex);
			philo->data->finished_philos[philo->id] = 1;
			pthread_mutex_unlock(&philo->data->finished_mutex);
			pthread_mutex_unlock(&philo->cycle_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->cycle_mutex);
	}
	if (philo->id % 2 == 0)
		return (eat(philo, 0));
	return (eat(philo, 1));
}

int	eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->fork);
	if (status(philo, 2))
	{
		pthread_mutex_unlock(&philo->left->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->fork);
	if (status(philo, 2))
	{
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	if (status(philo, 1))
		return (1);
	ms_sleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

int	odd_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (status(philo, 2))
	{
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left->fork);
	if (status(philo, 2))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->left->fork);
		return (1);
	}
	if (status(philo, 1))
		return (1);
	ms_sleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
	return (0);
}
