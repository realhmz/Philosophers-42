/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/09/28 14:50:53 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_philo_data *data, char **av)
{
	if (data->n_of_philos > 200 || data->n_of_philos <= 0)
		return (1);
	if (data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0)
		return (1);
	if (data->must_flag && data->t_must_eat <= 0)
	{
		return (1);
	}
	if (atoi_checker(av[1]) || atoi_checker(av[2])
		|| atoi_checker(av[3]) || atoi_checker(av[4]))
		return (1);
	if (data->must_flag)
		return (atoi_checker(av[5]));
	return (0);
}

int	parcing(t_philo *philo, int ac, char **av)
{
	philo->data->n_of_philos = ft_atoi(av[1]);
	philo->data->t_die = ft_atoi(av[2]);
	philo->data->t_eat = ft_atoi(av[3]);
	philo->data->t_sleep = ft_atoi(av[4]);
	philo->data->t_must_eat = 0;
	philo->data->must_flag = 0;
	if (ac == 6)
	{
		philo->data->t_must_eat = ft_atoi(av[5]);
		philo->data->must_flag = 1;
	}
	if (check_args(philo->data, av))
		return (1);
	philo->data->finished_philos = malloc
		(sizeof(int) * (philo->data->n_of_philos + 1));
	if (!philo->data->finished_philos)
	return (1);
	philo->data->time = 0;
	philo->data->finished_flag = 0;
	philo->data->flag = 1;
	memset(philo->data->finished_philos, 0,
		((philo->data->n_of_philos + 1) * sizeof(int)));
	return (0);
}

int	check_meals(t_philo *philo)
{
	int	len;
	int	i;

	i = 1;
	len = philo->data->n_of_philos;
	while (i <= len)
	{
		pthread_mutex_lock(&philo->data->finished_mutex);
		if (philo->data->finished_philos[i] == 0)
		{
			pthread_mutex_unlock(&philo->data->finished_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->finished_mutex);
		i++;
	}
	return (1);
}

int	check_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_of_philos)
	{
		pthread_mutex_lock(&philo->dead);
		if (philo->is_dead)
		{
			pthread_mutex_unlock(&philo->dead);
			return (1);
		}
		pthread_mutex_unlock(&philo->dead);
		philo = philo->right;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac != 5 && ac != 6)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	philo->data = malloc(sizeof(t_philo_data));
	if (!philo->data)
		return (1);
	philo->left = NULL;
	philo->right = NULL;
	if (parcing(philo, ac, av) != 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (philosophers(philo) != 0)
		return (1);
	while (!monitor(philo))
		philo = philo->right;
	sleep (1);
	ft_free(philo);
	return (0);
}
