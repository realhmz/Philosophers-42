/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reahmz <reahmz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/07/19 22:44:24 by reahmz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    parcing(t_philo *philo, int ac, char** av)
{
    philo->data.n_of_philos = ft_atoi(av[1]);
    philo->data.t_die = ft_atoi(av[2]);
    philo->data.t_eat = ft_atoi(av[3]);
    philo->data.t_sleep = ft_atoi(av[4]);
    if (philo->data.n_of_philos > 200 || philo->data.n_of_philos <= 0)
        return (1);
    if (ac == 6)
    {
        philo->data.t_must_eat = ft_atoi(av[5]);
        philo->data.must_flag = 1;
    }
    
    printf("philos %d\n", philo->data.n_of_philos);
    printf("t_die %ld\n", philo->data.t_die);
    printf("t_eat %ld\n", philo->data.t_eat);
    printf("t_sleep %ld\n", philo->data.t_sleep);
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
        while (1) ;
    
}

void    is_eating(t_philo *philo)
{
    
    if (philo->taken == 0 && philo->left->taken == 0)
    {
        pthread_mutex_lock(&philo->fork);
        pthread_mutex_lock(&philo->data.print);
        philo->taken = 1;
        pthread_mutex_unlock(&philo->data.print);
        pthread_mutex_unlock(&philo->fork);
        pthread_mutex_lock(&philo->left->fork);
        philo->left->taken = 1;
        philo->thinking = 0;
        status(philo, 1);
		philo->last_eat = what_time();
		ms_sleep(200);
        pthread_mutex_unlock(&philo->left->fork);
        pthread_mutex_lock(&philo->data.print);
        philo->left->taken = 0;
        // printf("id %d , Droped left fork\n", philo->id);
        pthread_mutex_unlock(&philo->data.print);
        philo->taken = 0;
        // printf("id %d , Droped right fork\n", philo->id);
    }
    if (philo->thinking == 0)
    {
        printf("%ld  %d  is thinking\n", what_time() - philo->timer, philo->id);
        philo->thinking = 1;
    }
    else
        is_eating(philo);
}

void    status(t_philo *philo, int action)
{
    pthread_mutex_lock(&philo->data.print);
    pthread_mutex_lock(&philo->last_meal_mutex);
    printf("%ld  ", what_time() - philo->timer);
    printf("%d  ",philo->id);
    if (action == 1)
        printf("is eating\n");
    if (action == 2)
        printf("Has takken right fork\n");
    if (action == 5)
        printf("Has takken left fork\n");
    if (action == 3)
        printf("is Thinking\n");
    if (action == 4)
        printf("is sleeping\n");
    pthread_mutex_unlock(&philo->last_meal_mutex);
    pthread_mutex_unlock(&philo->data.print);
    
}
