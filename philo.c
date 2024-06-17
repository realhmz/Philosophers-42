/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reahmz <reahmz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:55:53 by realhmz           #+#    #+#             */
/*   Updated: 2024/06/17 19:54:56 by reahmz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int philosophers(t_param *param)
{
    param->philo = malloc(sizeof(t_philo) * (param->n_of_philos));
    param->thread = malloc(sizeof(pthread_t) * (param->n_of_philos + 1));
    param->mutex = malloc(sizeof(pthread_mutex_t) * (param->n_of_philos));
    if (create_threads(param) != 0)
        return (1);
	if (create_mutex(param) != 0)
		return (1);
	
}

int create_threads(t_param *param)
{
    int	i;

	i = 0;
	while (i < param->n_of_philos)
	{
		if (pthread_create(&param->thread[i],NULL, &routine, (void *)param) != 0)
		{
			printf("ERROR\n");
			return (1);
		}
		pthread_join(param->thread[i],NULL);
		i++;
	}
	return (0);
}

int	create_mutex(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->n_of_philos)
	{
		if (pthread_mutex_init(&param->mutex[i], NULL) != 0)
			{
				printf("ERROR\n");
				return (1);
			}
		i++;
	}
	return (0);
}
int l = 0;
void	*routine(void *param)
{
	t_param *data;
	// static int l;
	data = (t_param *)param;
	int i = 0;
	while (i < 1000000)
	{
		l++;
		i++;
	}
	printf("%d\n",l);
}