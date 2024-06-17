/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reahmz <reahmz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:51 by reahmz            #+#    #+#             */
/*   Updated: 2024/06/17 19:07:52 by reahmz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int    parcing(t_param *param, int ac, char** av)
{
    param->n_of_philos = ft_atoi(av[1]);
    param->t_die = ft_atoi(av[2]);
    param->t_eat = ft_atoi(av[3]);
    param->t_sleep = ft_atoi(av[4]);
    if (param->n_of_philos > 200 || param->n_of_philos <= 0)
        return (1);
    if (ac == 6)
    {
        param->t_must_eat = ft_atoi(av[5]);
        param->must_flag = 1;
        printf("t_must_eat %d\n", param->must_flag);
    }
    
    printf("params %d\n", param->n_of_philos);
    printf("t_die %d\n", param->t_die);
    printf("t_eat %d\n", param->t_eat);
    printf("t_sleep %d\n", param->t_sleep);
    return (0);
}
int main(int ac, char **av)
{
    t_param *param;
    param = NULL;
    if (ac != 5 && ac != 6)
        return (1);
    param = malloc(sizeof(t_param));
    if (parcing(param, ac, av) != 0)
        return (1);
    if (philosophers(param) != 0)
        return (1);
    
}