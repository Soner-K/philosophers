/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:03:32 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/08 14:22:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

// dont forget if number_win is defined
// careful lock a mutex that is already locked (same with unlocking)

void	ft_usleep(unsigned int seconds)
{
	long	to_sleep;

	to_sleep = seconds * 1000;
	if (to_sleep > UINT_MAX)
		return ;
	usleep(to_sleep);
}

void	ft_sleep(t_philo *philo, long time)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(args->sleep_lock);
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(args->sleep_lock);
	ft_usleep(time);
}

void	ft_eat(t_philo *philo, long time)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(args->write_lock);
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(args->write_lock);
	ft_usleep(time);
}

void	ft_think(t_philo *philo, long time)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(args->write_lock);
	printf("%d is thinking\n", philo->id);
	pthread_mutex_unlock(args->write_lock);
	ft_usleep(time);
}

void	do_routine(t_philo *philos, t_args *args)
{
	short int i;

	i = -1;
	while (i++ < args->n)
		pthread_create(&philos->thread, NULL, life, &philos[i]);
}

void	*life(t_philo *philo)
{
	t_args	*args;

	args = (t_args *)philo->args;
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(args->write_lock);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(args->write_lock);
	pthread_mutex_lock(philo->fork_r);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(args->write_lock);
	ft_eat(philo, args->time_eat);
	ft_sleep(philo, args->time_sleep);
	ft_think(philo, args->time_sleep);
	// ft_think;
}
