/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/08/21 19:26:31 by het-taja         ###   ########.fr       */
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
	philo->data = malloc(sizeof(t_philo_data));
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
	philo->data->finished_philos = malloc(sizeof(int) * philo->data->n_of_philos + 1);
	philo->data->time = 0;
	philo->data->finished_flag = 0;
	philo->data->flag = 1;
	memset(philo->data->finished_philos, 0, philo->data->n_of_philos+1 * sizeof(int));
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
		if (!philo->is_dead)
			return (1);
		philo = philo->right;
		i++;
	}
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
	philo->left = NULL;
	philo->right = NULL;
	if (parcing(philo, ac, av) != 0)
		return (1);
	if (philosophers(philo) != 0)
		return (1);

	while (philo)
	{
		if (check_meals(philo))
		{
			philo->data->finished_flag = 1;
			return (0);
		}
		pthread_mutex_lock(&philo->data->flag_mutex);
		time = what_time() - philo->last_eat;
		if (time > philo->data->t_die )
		{
			philo->data->flag = 0;
			pthread_mutex_unlock(&philo->data->flag_mutex);
			while (check_dead(philo)) ;
			pthread_mutex_lock(&philo->data->print);
			pthread_mutex_lock(&philo->data->time_mutex);
			printf("%ld  %d  is dead\n", time , philo->id);	
			pthread_mutex_unlock(&philo->data->time_mutex);
			pthread_mutex_unlock(&philo->data->print);
			return (0);
		}
			pthread_mutex_unlock(&philo->data->flag_mutex);
			philo = philo->right;
		}
}

int    is_eating(t_philo *philo)
{
	if (philo->data->must_flag && philo->cycle == philo->data->t_must_eat)
	{
		pthread_mutex_lock(&philo->data->finished_mutex);
		philo->data->finished_philos[philo->id] = 1;
		pthread_mutex_unlock(&philo->data->finished_mutex);
	}
	if (status(philo, 0))
		return (1);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->left->fork);
		if (status(philo, 5) || philo->data->n_of_philos == 1)
			return (1);
		pthread_mutex_lock(&philo->fork);
		if(status(philo, 2) || status(philo, 1))
			return (1);
		philo->cycle++;
		philo->last_eat = what_time();
		ms_sleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		if (status(philo, 2))
			return (1);
		pthread_mutex_lock(&philo->left->fork);
		if(status(philo, 5) || status(philo, 1))
			return (1);
		philo->cycle++;
		philo->last_eat = what_time();
		ms_sleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->left->fork);	
	}
	return (0);
}

int	status(t_philo *philo, int action)
{
	// pthread_mutex_lock(&philo->last_meal_mutex);
	
	size_t	time;

	// if (philo->data->flag == 2)
	// {
	// 	pthread_mutex_unlock(&philo->data->flag_mutex);
	// 	return (1);
	// }
	pthread_mutex_lock(&philo->data->flag_mutex);
	if (philo->data->flag == 0)
	{
		// pthread_mutex_lock(&philo->data->print);
		// pthread_mutex_lock(&philo->data->time_mutex);
		// printf("%ld  %d  is dead\n",what_time() - philo->data->time, philo->id);
		// pthread_mutex_unlock(&philo->data->time_mutex);
		// pthread_mutex_unlock(&philo->data->print);
		
		// philo->data->flag = 2;
		pthread_mutex_unlock(&philo->data->flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->flag_mutex);
	
	if (action == 0)
		return 0;
	pthread_mutex_lock(&philo->data->time_mutex);
	time = what_time() - philo->data->time;
	pthread_mutex_unlock(&philo->data->time_mutex);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  ", time);
	printf("%d  ",philo->id);
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
