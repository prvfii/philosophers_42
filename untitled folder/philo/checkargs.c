/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:46:26 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:33:45 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_content(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	verifparams(char **av)
{
	if (check_arg_content(av[1]) == 1 && ft_atoi(av[1]) > PHILO_MAX)
		return (1);
	if (check_arg_content(av[2]) == 1)
		return (1);
	if (check_arg_content(av[3]) == 1)
		return (1);
	if (check_arg_content(av[4]) == 1)
		return (1);
	if (av[5])
		if (check_arg_content(av[5]) == 1)
			return (1);
	return (0);
}
