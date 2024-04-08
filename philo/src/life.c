/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:03:32 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/08 13:01:23 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

// dont forget if number_win is defined
// careful lock a mutex that is already locked (same with unlocking)
void	*life(t_philo *philos)
{
	t_args	*args;

	args = philos->args;
	pthread_mutex_lock(philos->fork_l);
	pthread_mutex_lock(args->write_lock);
	printf("%d has taken a fork\n", philos->id);
	pthread_mutex_unlock(args->write_lock);
	pthread_mutex_lock(philos->fork_r);
	printf("%d has taken a fork\n", philos->id);
	pthread_mutex_unlock(args->write_lock);
	ft_eat(philos);
	//ft_sleep;
	//ft_think;
}

void	ft_sleep(t_philo philo)
{
}

void	ft_eat(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(args->write_lock);
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(args->write_lock);
}

void	ft_think(t_philo philo)
{
}

void	do_routine(t_philo *philos, t_args *args)
{
	short int i;

	i = -1;
	while (i++ < args->n)
		pthread_create(&philos->thread, NULL, life, &philos[i]);
}