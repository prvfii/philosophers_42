/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:39:51 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:33:58 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		p[PHILO_MAX];
	t_global	s;
	t_info		i;

	if ((ac != 5 && ac != 6) || verifparams(av) == 1)
		return (ft_error("Problem with the params\n"));
	s.philos_finished = 0;
	initparams(&p[0], av);
	initphilos(p, &s, &i, av);
	initforks(i.forks, av);
	initmutexes(&s, p, &i);
	ft_simulation(p, ft_atoi(av[1]));
	destroy_mutexes(p, &s, p[0].n_philo);
	return (0);
}
