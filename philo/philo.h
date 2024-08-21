/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:34:02 by reahmz            #+#    #+#             */
/*   Updated: 2024/08/21 11:38:43 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>


// typedef struct s_philo
// {
// 	int	t_last_eat;
// 	int	is_dead;
// 	int	is_thinking;
// 	int	is_eating;
// 	int	is_sleeping;
// 	int	using_fork;
// 	int	id;
// } t_philo;


typedef struct s_philo_data
{
	int				n_of_philos;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			t_must_eat;
	long			must_flag;
	int				*finished_philos;
	int				finished_flag;
	size_t			time;
	pthread_mutex_t	print;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	flag_mutex;
	int				flag;
}	t_philo_data;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	long			cycle;
	t_philo_data	*data;
	pthread_t		philo;
	long			last_eat;
	pthread_mutex_t	fork;
	struct s_philo	*right;
	struct s_philo	*left;
}	t_philo;


// typedef struct s_params
// {
// 	int n_of_philos;
// 	int t_die;
// 	int t_eat;
// 	int t_sleep;
// 	int	t_must_eat;
// 	int	must_flag;
// 	t_philo *philo;
// 	pthread_mutex_t	*mutex;
// 	pthread_t *thread;

// } t_philo;

int	ft_atoi(const char *nptr);
int ft_strlen(char *str);
int philosophers(t_philo *param);
int create_threads(t_philo *param);
int	create_mutex(t_philo *param);
void	*routine(void *param);
size_t    what_time();
int    ms_sleep(size_t milliseconds);
void    ft_lst_add_back(t_philo *philo, t_philo *new, int id);
// void    fill_data(t_philo *philo);
int	create_list(t_philo *philo);
t_philo	*ft_lstnew(t_philo_data *data);
void    print_data(t_philo_data *data);
int	status(t_philo *philo, int action);
int    is_eating(t_philo *philo);
int	ft_exit(t_philo *philo);
int	is_sleeping(t_philo *philo);

#endif