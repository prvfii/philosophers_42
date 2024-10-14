/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:41 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/03 16:20:22 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <stdatomic.h>
# include <sys/time.h>

# define PHILO_MAX 200

typedef struct s_global
{
	atomic_int		dead_flag;
	int				philos_finished;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_global;

typedef struct s_info
{
	struct s_philo	*philos;
	t_global		*global;
	pthread_mutex_t	forks[PHILO_MAX];
}					t_info;

typedef struct s_philo
{
	int				id;
	int				n_philo;
	atomic_int		is_eating;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				times_to_eat;
	atomic_int		meals_eaten;
	atomic_size_t	start;
	atomic_size_t	last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	t_info			*info;
}					t_philo;

int					verifparams(char **av);
int					check_arg_content(char *av);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				initparams(t_philo *p, char **av);
size_t				get_current_time(void);
void				initphilos(t_philo *p, t_global *s, t_info *i, char **av);
void				initforks(pthread_mutex_t *f, char **av);
void				initmutexes(t_global *s, t_philo *p, t_info *i);
int					ft_strlen(char *str);
int					ft_error(char *str);
void				print_message(t_philo *p, char *action);
void				ft_usleep(size_t milliseconds);
void				philo_eat(t_philo *p);
void				philo_take_forks(t_philo *p);
void				philo_sleep(t_philo *p);
void				philo_think(t_philo *p);
void				*philo_routine(void *ar);
int					ft_simulation(t_philo *p, int n_philo);
void				*ft_checker(void *arg);
void				destroy_mutexes(t_philo *p, t_global *g, int n_philo);

#endif