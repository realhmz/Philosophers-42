/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realhmz <realhmz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:34:02 by reahmz            #+#    #+#             */
/*   Updated: 2024/06/12 15:53:25 by realhmz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int	ft_atoi(const char *nptr);
int ft_strlen(char *str);

typedef struct s_philo
{
	int	t_last_eat;
	int	is_dead;
	int	is_thinking;
	int	is_eating;
	int	is_sleeping;
	int	using_fork;
	pthread_mutex_t	food;
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	pthread_mutex_t	has_fork;
} t_philo;

typedef struct s_params
{
	int philos;
	int t_die;
	int t_eat;
	int t_sleep;
	int	t_must_eat;
	int	must_flag;
	t_philo *philo;

} t_param;

#endif