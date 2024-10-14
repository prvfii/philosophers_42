/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:50:13 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:33:53 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initparams(t_philo *p, char **av)
{
	p->n_philo = ft_atoi(av[1]);
	p->t_die = ft_atoi(av[2]);
	p->t_eat = ft_atoi(av[3]);
	p->t_sleep = ft_atoi(av[4]);
	if (av[5])
		p->times_to_eat = ft_atoi(av[5]);
	else
		p->times_to_eat = -1;
}

void	initphilos(t_philo *p, t_global *s, t_info *i, char **av)
{
	int	n_philo;
	int	idx;

	idx = 0;
	n_philo = ft_atoi(av[1]);
	while (idx < n_philo)
	{
		p[idx].id = idx + 1;
		initparams(&p[idx], av);
		p[idx].start = get_current_time();
		p[idx].meals_eaten = 0;
		p[idx].is_eating = 0;
		p[idx].last_meal = get_current_time();
		p[idx].write_lock = &s->write_lock;
		p[idx].meal_lock = &s->meal_lock;
		p[idx].dead_lock = &s->dead_lock;
		p[idx].info = i;
		p[idx].l_fork = &i->forks[idx];
		p[idx].r_fork = &i->forks[(idx + 1) % n_philo];
		idx++;
	}
}

void	initmutexes(t_global *s, t_philo *p, t_info *i)
{
	s->dead_flag = 0;
	s->philos_finished = 0;
	if (pthread_mutex_init(&s->dead_lock, NULL) != 0)
		ft_error("Error initializing dead_lock mutex\n");
	if (pthread_mutex_init(&s->meal_lock, NULL) != 0)
		ft_error("Error initializing meal_lock mutex\n");
	if (pthread_mutex_init(&s->write_lock, NULL) != 0)
		ft_error("Error initializing write_lock mutex\n");
	i->global = s;
	i->philos = p;
}

void	initforks(pthread_mutex_t *f, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_mutex_init(&f[i], NULL) != 0)
			ft_error("Error initializing fork mutex\n");
		i++;
	}
}
