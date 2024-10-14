/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:58:23 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:34:10 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
	{
		usleep(200);
	}
	while (p->info->global->dead_flag != 1)
	{
		philo_take_forks(p);
		philo_eat(p);
		philo_sleep(p);
		philo_think(p);
	}
	return (NULL);
}
