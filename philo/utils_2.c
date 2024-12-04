/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:29:29 by het-taja          #+#    #+#             */
/*   Updated: 2024/11/09 17:30:14 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_philo *philo)
{
	if (philo->data->must_flag && check_meals(philo))
		return (1);
	if (check_dead(philo))
		return (1);
	if (check_time(philo))
		return (1);
	return (0);
}

void	*monitor_check(void	*param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (!monitor(philo))
		philo = philo->right;
	return (NULL);
}
