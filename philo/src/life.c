/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:03:32 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/16 15:31:46 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Sleeps for time miliseconds and then thinks.
 * @param philo A pointer to the id philo's structure.
 * @param time The time for which to sleep.
 * @returns void.
 */
static void	sleep_and_think(t_philo *philo, long time)
{
	philo_printf("is sleeping", philo, (t_args *)philo->args, 0);
	ft_usleep(time, philo->args);
	philo_printf("is thinking", philo, (t_args *)philo->args, 0);
	if (philo->args->n % 2)
	{
		ft_usleep(philo->args->time_eat * 2 - philo->args->time_sleep,
			philo->args);
	}
}

/**
 * @brief The eating function for the even id'd philosophers.
 * This is done to avoid dead lock.
 * @param philo A pointer to the id philo's structure.
 * @param time The time for which to eat.
 * @returns void.
 */
static void	ft_eat_even(t_philo *philo, long time)
{
	pthread_mutex_lock(philo->fork_r);
	philo_printf("has taken a fork", philo, philo->args, 0);
	if (philo->args->n == 1)
	{
		ft_usleep(philo->args->time_die, philo->args);
		pthread_mutex_unlock(philo->fork_r);
		return ;
	}
	pthread_mutex_lock(philo->fork_l);
	philo_printf("has taken a fork", philo, philo->args, 0);
	philo_printf("is eating", philo, philo->args, 0);
	pthread_mutex_lock(&philo->args->eat_lock);
	philo->meals++;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->args->eat_lock);
	ft_usleep(time, philo->args);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

/**
 * @brief The eating function for the odd id'd philosophers.
 * This is done to avoid dead lock.
 * @param philo A pointer to the id philo's structure.
 * @param time The time for which to eat.
 * @returns void.
 */
static void	ft_eat_odd(t_philo *philo, long time)
{
	pthread_mutex_lock(philo->fork_l);
	philo_printf("has taken a fork", philo, philo->args, 0);
	pthread_mutex_lock(philo->fork_r);
	philo_printf("has taken a fork", philo, philo->args, 0);
	philo_printf("is eating", philo, philo->args, 0);
	pthread_mutex_lock(&philo->args->eat_lock);
	philo->meals++;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->args->eat_lock);
	ft_usleep(time, philo->args);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

/**
 * @brief Checks if all philosopher are alive.
 * @param args A pointer to the args' structure.
 * @returns FALSE (0) if a philosopher died, and TRUE (1) otherwise.
 */
char	not_dead(t_args *args)
{
	pthread_mutex_lock(&args->dead_lock);
	if (args->dead == 1)
	{
		pthread_mutex_unlock(&args->dead_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&args->dead_lock);
	return (TRUE);
}

/**
 * @brief Does the routine (eat, sleep, think).
 * @param param A void pointer to a given philosopher's structure.
 * @returns NULL.
 */
void	*life(void *param)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)param;
	args = (t_args *)philo->args;
	if (philo->id % 2 == 0)
		ft_usleep(1, args);
	while (not_dead(args))
	{
		if (philo->id % 2 == 0 || args->n == 1)
			ft_eat_even(philo, args->time_eat);
		else if (philo->id % 2 == 1)
			ft_eat_odd(philo, args->time_eat);
		sleep_and_think(philo, args->time_sleep);
	}
	return (NULL);
}
