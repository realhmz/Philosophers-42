/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/08/19 23:00:08 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    parcing(t_philo *philo, int ac, char** av)
{
	philo->data = malloc(sizeof(t_philo_data));
	philo->data->n_of_philos = ft_atoi(av[1]);
	philo->data->t_die = ft_atoi(av[2]);
	philo->data->t_eat = ft_atoi(av[3]);
	philo->data->t_sleep = ft_atoi(av[4]);
	if (philo->data->n_of_philos > 200 || philo->data->n_of_philos <= 0)
		return (1);
	philo->data->t_must_eat = 0;
	philo->data->must_flag = 0;
	if (ac == 6)
	{
		philo->data->t_must_eat = ft_atoi(av[5]);
		philo->data->must_flag = 1;
	}
	philo->data->last_meal = 0;
	philo->data->time = 0;
	philo->data->flag = 1;
	// printf("philos %d\n", philo->data.n_of_philos);
	// printf("t_die %ld\n", philo->data.t_die);
	// printf("t_eat %ld\n", philo->data.t_eat);
	// printf("t_sleep %ld\n", philo->data.t_sleep);
	return (0);
}
int main(int ac, char **av)
{
	t_philo *philo;
	philo = NULL;
	if (ac != 5 && ac != 6)
		return (1);
	philo = malloc(sizeof(t_philo));
	philo->left = NULL;
	philo->right = NULL;
	if (parcing(philo, ac, av) != 0)
		return (1);
	if (philosophers(philo) != 0)
		return (1);
	while (1)
	{
		while (philo)
		{
			if ((what_time() - philo->last_eat) > philo->data->t_die)
			{
				pthread_mutex_lock(&philo->data->print);
				printf("%ld  %d  is dead\n",what_time() - philo->data->time, philo->id);
				pthread_mutex_unlock(&philo->data->print);
				philo->data->flag = 0;
				exit (1);
			}
			philo = philo->right;
		}
	}
}

int    is_eating(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->left->fork);
		status(philo, 5);
		pthread_mutex_lock(&philo->fork);
		status(philo, 2);
		status(philo, 1);
		philo->last_eat = what_time();
		ms_sleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		status(philo, 2);
		pthread_mutex_lock(&philo->left->fork);
		status(philo, 5);
		status(philo, 1);
		philo->last_eat = what_time();
		ms_sleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->left->fork);	
	}
	return (0);
}

void    status(t_philo *philo, int action)
{
	// pthread_mutex_lock(&philo->last_meal_mutex);
	
	size_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = what_time() - philo->data->time;
	printf("%ld  ", time);
	printf("%d  ",philo->id);

	if (action == 1)
	{
		printf("is eating\n");
	}
	if (action == 2)
		printf("Has takken right fork\n");
	if (action == 5)
		printf("Has takken left fork\n");
	if (action == 3)
		printf("is Thinking\n");
	if (action == 4)
		printf("is sleeping\n");
	pthread_mutex_unlock(&philo->data->print);
}
