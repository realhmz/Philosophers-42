/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realhmz <realhmz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:55:53 by realhmz           #+#    #+#             */
/*   Updated: 2024/06/12 16:04:00 by realhmz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int philosophers(t_param *param)
{
    if (creat_threads(param) != 0)
        return (1);
}

int creat_threads(t_param *param)
{
    t_philo *philos;

    param->philo = malloc(sizeof(t_philo) * (param->philos + 1));
}