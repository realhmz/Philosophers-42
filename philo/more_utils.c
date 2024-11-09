/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:47:53 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/09 14:29:52 by het-taja         ###   ########.fr       */
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

int	destroy(t_philo *philo)
{
	int	len;

	len = philo->data->n_of_philos;
	free(philo->data->finished_philos);
	pthread_mutex_destroy(&philo->data->finished_mutex);
	pthread_mutex_destroy(&philo->data->print);
	pthread_mutex_destroy(&philo->data->flag_mutex);
	pthread_mutex_destroy(&philo->data->time_mutex);
	free(philo->data);
	if (len == 1)
		free(philo);
	return (len);
}

int	ft_free(t_philo *philo)
{
	int		i;
	int		len;
	t_philo	*tmp;

	i = 0;
	len = destroy(philo);
	if (len > 1)
	{
		while (i < len)
		{
			pthread_mutex_destroy(&philo->cycle_mutex);
			pthread_mutex_destroy(&philo->last_eat_mutex);
			pthread_mutex_destroy(&philo->fork);
			pthread_mutex_destroy(&philo->dead);
			tmp = philo;
			philo = philo->right;
			free(tmp);
			tmp = NULL;
			i++;
		}
	}
	return (1);
}

int	is_mat(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	if (time - philo->last_eat > philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->last_eat_mutex);
		pthread_mutex_lock(&philo->data->flag_mutex);
		philo->data->flag = 0;
		pthread_mutex_unlock(&philo->data->flag_mutex);
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
