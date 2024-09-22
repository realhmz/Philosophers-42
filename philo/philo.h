/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:34:02 by reahmz            #+#    #+#             */
/*   Updated: 2024/09/22 23:35:58 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo_data
{
	int				n_of_philos;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			t_must_eat;
	int				must_flag;
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
	pthread_mutex_t	dead;
	pthread_mutex_t	cycle_mutex;
	pthread_mutex_t	last_eat_mutex;
	struct s_philo	*right;
	struct s_philo	*left;
}	t_philo;

int		ft_atoi(const char *nptr);
int		ft_strlen(char *str);
int		philosophers(t_philo *param);
int		create_threads(t_philo *param);
int		create_mutex(t_philo *param);
void	*routine(void *param);
size_t	what_time(void);
int		ms_sleep(size_t milliseconds);
void	ft_lst_add_back(t_philo *philo, t_philo *new, int id);
int		create_list(t_philo *philo);
t_philo	*ft_lstnew(t_philo_data *data);
int		eat(t_philo *philo, int action);
int		eat_even(t_philo *philo);
void	print_data(t_philo_data *data);
int		status(t_philo *philo, int action);
int		is_eating(t_philo *philo);
int		odd_eat(t_philo *philo);
int		ft_exit(t_philo *philo);
int		is_sleeping(t_philo *philo);
void	detach_all(t_philo *philo);
int		ft_free(t_philo *philo);
int		is_mat(t_philo *philo, long time);
int		check_time(t_philo *philo);
int		monitor(t_philo *philo);
int		check_meals(t_philo *philo);
int		check_dead(t_philo *philo);
int		atoi_checker(char *str);

#endif