/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:59:44 by het-taja          #+#    #+#             */
/*   Updated: 2024/08/28 15:42:50 by het-taja         ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->dead);

	return (1);
}

void	*routine(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	
	 if (philo->id % 2 == 0)
	 	usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->data->finished_mutex);
		if (philo->data->finished_flag)
		{
			pthread_mutex_unlock(&philo->data->finished_mutex);
			ft_exit(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->finished_mutex);
		if (is_eating(philo) || is_sleeping(philo))
		{
			ft_exit(philo);
			return(NULL);
		}
	}
	return(philo);
}

int eat_even(t_philo *philo)
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
int odd_eat(t_philo *philo)
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

int eat(t_philo *philo, int action)
{
    if (action == 0 && odd_eat(philo))
        return (1);
    else if(action && eat_even(philo))
            return(1);
    pthread_mutex_lock(&philo->cycle_mutex);
    philo->cycle++;
    pthread_mutex_unlock(&philo->cycle_mutex);
    pthread_mutex_lock(&philo->last_eat_mutex);
    philo->last_eat = what_time();
    pthread_mutex_unlock(&philo->last_eat_mutex);
    return (0);
}

int is_eating(t_philo *philo)
{
    if (status(philo, 0))
        return (1);
    if (philo->data->must_flag)
    {
        pthread_mutex_lock(&philo->cycle_mutex);
        if (philo->data->t_must_eat == philo->cycle)
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
        return(eat(philo, 0));
    return(eat(philo, 1));
}

int status(t_philo *philo, int  action)
{
    size_t  time;
    pthread_mutex_lock(&philo->data->flag_mutex);
    if (!philo->data->flag)
    {
        pthread_mutex_unlock(&philo->data->flag_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->flag_mutex);
    if (!action)
        return (0);
	pthread_mutex_lock(&philo->data->time_mutex);
	time = what_time() - philo->data->time;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld  ", time);
	pthread_mutex_unlock(&philo->data->time_mutex);
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