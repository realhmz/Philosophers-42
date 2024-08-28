/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/08/28 14:38:14 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_args(t_philo_data *data)
{
	if (data->n_of_philos > 200 || data->n_of_philos <= 0)
		return (1);
	if (data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0)
		return (1);
	if (data->must_flag && data->t_must_eat <= 0)
	{
		return (1);
	}
	
	return (0);
}

int    parcing(t_philo *philo, int ac, char** av)
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
	if (check_args(philo->data))
		return (1);
	philo->data->finished_philos = malloc(sizeof(int) * (philo->data->n_of_philos + 1));
	philo->data->time = 0;
	philo->data->finished_flag = 0;
	philo->data->flag = 1;
	memset(philo->data->finished_philos, 0, ((philo->data->n_of_philos + 1) * sizeof(int)));
	return (0);
}
int		check_meals(t_philo *philo)
{
	int	len;
	int	i;

	i = 1;
	len = philo->data->n_of_philos;
	while (i <= len)
	{
		if (philo->data->finished_philos[i] == 0)
		{
			return (0);
		}
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
		if (!philo->is_dead)
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
int ft_free(t_philo *philo)
{
	int	i;
	int	len;

	i = 0;
	len = philo->data->n_of_philos;
	free(philo->data->finished_philos);
	free(philo->data);
	if (len == 1)
		free(philo);
	// while (i < len)
	// {
	// 	free(philo->left);
	// 	philo = philo->right;
	// 	i++;
	// }
	// philo->data = NULL;
	
	return (0);
}
int	monitor(t_philo *philo)
{
	return (0);
}
int main(int ac, char **av)
{
	t_philo *philo;
	size_t	time;
	philo = NULL;
	if (ac != 5 && ac != 6)
		return (1);
	philo = malloc(sizeof(t_philo));
	philo->data = malloc(sizeof(t_philo_data));
	printf("%p\n",philo);
	philo->left = NULL;
	philo->right = NULL;
	if (parcing(philo, ac, av) != 0)
		return (1);
	if (philosophers(philo) != 0)
		return (1);
	while (!monitor(philo))
		philo = philo->right;
	return (0);
}
