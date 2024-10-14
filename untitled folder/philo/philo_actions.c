/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:59:47 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:34:05 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *p)
{
	if (p->id % 2 == 1)
	{
		pthread_mutex_lock(p->l_fork);
		print_message(p, "has taken a fork\n");
		if (p->n_philo == 1)
		{
			ft_usleep(p->t_die);
			print_message(p, "died\n");
			pthread_mutex_unlock(p->l_fork);
			p->info->global->dead_flag = 1;
			return ;
		}
		pthread_mutex_lock(p->r_fork);
		print_message(p, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(p->r_fork);
		print_message(p, "has taken a fork\n");
		pthread_mutex_lock(p->l_fork);
		print_message(p, "has taken a fork\n");
	}
}

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->meal_lock);
	p->is_eating = 1;
	p->last_meal = get_current_time();
	print_message(p, "is eating\n");
	p->meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	ft_usleep(p->t_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	p->is_eating = 0;
}

void	philo_sleep(t_philo *p)
{
	print_message(p, "is sleeping\n");
	ft_usleep(p->t_sleep);
}

void	philo_think(t_philo *p)
{
	print_message(p, "is thinking\n");
}
