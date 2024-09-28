/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:24:57 by reahmz            #+#    #+#             */
/*   Updated: 2024/09/28 14:06:33 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	what_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ms_sleep(size_t milliseconds)
{
	size_t	start;

	start = what_time();
	while ((what_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	ft_lst_add_back(t_philo *philo, t_philo *new, int id)
{
	t_philo	*head;

	head = philo;
	new->id = id;
	if (!head)
	{
		head = new;
		return ;
	}
	while (head)
	{
		if (head->right)
			head = head->right;
		else
		{
			head->right = new;
			return ;
		}
	}
}

t_philo	*ft_lstnew(t_philo_data *data)
{
	t_philo	*head;

	head = (t_philo *)malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	head->data = data;
	head->right = NULL;
	return (head);
}
