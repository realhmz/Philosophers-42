/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:47:53 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/22 23:01:48 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_all(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = philo->data->n_of_philos;
	while (i < j)
	{
		pthread_detach(philo->philo);
		i++;
		philo = philo->right;
	}
}

int	ft_free(t_philo *philo)
{
	int	i;
	int	len;

	i = 0;
	len = philo->data->n_of_philos;
	free(philo->data->finished_philos);
	free(philo->data);
	if (len == 1)
		free(philo);
	else
	{
		while (i < len)
		{
			free(philo->left);
			philo = philo->right;
			i++;
		}
	}
	philo->data = NULL;
	return (1);
}

int	is_mat(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	if (time - philo->last_eat > philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (0);
}

int	check_time(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->time_mutex);
	time = what_time();
	if (is_mat(philo, time))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld  %d  is dead\n", time - philo->data->time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->time_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->time_mutex);
	return (0);
}

int	monitor(t_philo *philo)
{
	if (check_meals(philo))
		return (ft_free(philo));
	if (check_dead(philo))
		return (ft_free(philo));
	if (check_time(philo))
		return (ft_free(philo));
	return (0);
}