/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reahmz <reahmz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/06/12 14:54:00 by reahmz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    parcing(t_philo *philo, int ac, char** av)
{
    philo->philos = ft_atoi(av[1]);
    philo->t_die = ft_atoi(av[2]);
    philo->t_eat = ft_atoi(av[3]);
    philo->t_sleep = ft_atoi(av[4]);
    if (philo->philos > 200 || philo->philos <= 0)
        return (1);
    if (ac == 6)
    {
        philo->t_must_eat = ft_atoi(av[5]);
        philo->must_flag = 1;
    }
    
    printf("philos %d\n", philo->philos);
    printf("t_die %d\n", philo->t_die);
    printf("t_eat %d\n", philo->t_eat);
    printf("t_sleep %d\n", philo->t_sleep);
    printf("t_sleep %d\n", philo->t_sleep);
    return (0);
}
int main(int ac, char **av)
{
    t_philo *philo;
    philo = NULL;
    // if (ac != 5 && ac != 6)
    //     return (1);
    philo = malloc(sizeof(t_philo));
    if (parcing(philo, ac, av) != 0)
        return (1);
    
    
}