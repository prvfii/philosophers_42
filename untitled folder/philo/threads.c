/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:28:40 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:34:16 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_checker(void *arg)
{
	t_philo	*p;
	int		i;
	size_t	time_since_last_meal;

	p = (t_philo *)arg;
	while (p->info->global->dead_flag != 1)
	{
		i = 0;
		while (i < p->n_philo)
		{
			pthread_mutex_lock(p[i].meal_lock);
			time_since_last_meal = get_current_time() - p[i].last_meal;
			if (p->meals_eaten >= p->times_to_eat && p->times_to_eat != -1)
				p->info->global->dead_flag = 1;
			if (time_since_last_meal > p[i].t_die)
				return (print_message(p, "died\n"),
					p->info->global->dead_flag = 1,
					pthread_mutex_unlock(p[i].meal_lock), NULL);
			pthread_mutex_unlock(p[i].meal_lock);
			usleep(1);
			i++;
		}
	}
	return (NULL);
}

int	ft_simulation(t_philo *p, int n_philo)
{
	pthread_t	checker;
	int			i;

	i = -1;
	if (pthread_create(&checker, NULL, ft_checker, &p[0]) != 0)
		return (destroy_mutexes(p, p->info->global, n_philo),
			ft_error("Error creating a philo thread\n"));
	while (++i < n_philo)
	{
		if (pthread_create(&p[i].thread, NULL, philo_routine, &p[i]) != 0)
			return (destroy_mutexes(p, p->info->global, n_philo),
				ft_error("Error creating a philo thread\n"));
	}
	i = 0;
	if (pthread_join(checker, NULL) != 0)
		return (destroy_mutexes(p, p->info->global, n_philo),
			ft_error("Problem with join\n"));
	while (i < n_philo)
	{
		if (pthread_join(p[i].thread, NULL) != 0)
			return (destroy_mutexes(p, p->info->global, n_philo),
				ft_error("Problem with join\n"));
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_philo *p, t_global *g, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_destroy(p[i].l_fork);
		pthread_mutex_destroy(p[i].r_fork);
		pthread_mutex_destroy(p[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&g->write_lock);
	pthread_mutex_destroy(&g->meal_lock);
	pthread_mutex_destroy(&g->dead_lock);
}
