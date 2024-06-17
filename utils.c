/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reahmz <reahmz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:24:57 by reahmz            #+#    #+#             */
/*   Updated: 2024/06/17 20:32:37 by reahmz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    what_time()
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 100 + time.tv_usec / 1000);
}

void    ms_sleep(int time)
{
    long    start;

    start = what_time();
    while (what_time() - start < time)
        usleep(100);
}
