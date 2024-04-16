/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:37:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/16 14:38:26 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Checks for the death of one given philosopher.
 * @returns TRUE (1) if a given philosopher died, and FALSE (0) otherwise.
 */
static char	death_one(t_philo *philo, t_args *args)
{
	long	current_time;
	long	delay;

	pthread_mutex_lock(&args->eat_lock);
	current_time = get_time();
	if (philo->last_ate != 0)
		delay = current_time - philo->last_ate;
	else
		delay = current_time - args->beginning_time;
	if (delay >= args->time_die)
	{
		pthread_mutex_unlock(&args->eat_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&args->eat_lock);
	return (FALSE);
}

/**
 * @brief Looks for a dead philosopher among all the philosophers.
 * @returns TRUE (1) if at least one philosopher died, and FALSE (0) otherwise.
 */
static char	death_all(t_philo *philos, t_args *args)
{
	short int	i;

	i = -1;
	while (++i < args->n)
	{
		if (death_one(&philos[i], args) == TRUE)
		{
			pthread_mutex_lock(&args->dead_lock);
			args->dead = 1;
			pthread_mutex_unlock(&args->dead_lock);
			philo_printf("died", &philos[i], args, 1);
			return (TRUE);
		}
	}
	return (FALSE);
}

/**
 * @brief If the optional parameter is given, checks if
 * all the philosophers ate the required amount of meals.
 * @returns TRUE (1) if all the philosophers ate the required amount of meals
 * and 0 otherwise.
 */
static char	all_meals(t_philo *philos, t_args *args)
{
	short int	i;
	int			finished;

	i = -1;
	finished = 0;
	while (++i < args->n)
	{
		pthread_mutex_lock(&args->eat_lock);
		if (philos[i].meals >= args->number_win)
			finished++;
		pthread_mutex_unlock(&args->eat_lock);
	}
	pthread_mutex_lock(&args->dead_lock);
	if (finished >= args->n)
	{
		return (args->dead = 1, pthread_mutex_unlock(&args->dead_lock), TRUE);
	}
	pthread_mutex_unlock(&args->dead_lock);
	return (FALSE);
}

/**
 * @brief The watcher's thread checks if the condition to stop the simulation
 * is encountered (a philosopher died, or they all ate the required number
 * of meals.
 * @param param A void pointer to the philosophers' structure.
 * @returns NULL.
 */
void	*watch_philos(void *param)
{
	t_philo		*philos;
	t_args		*args;
	short int	i;

	philos = (t_philo *)param;
	args = (t_args *)philos->args;
	i = 0;
	pthread_mutex_lock(&args->access_lock);
	args->beginning_time = get_time();
	pthread_mutex_unlock(&args->access_lock);
	if (args->optional == 0)
	{
		while (!death_all(philos, args))
			;
	}
	else
	{
		while (!death_all(philos, args) && !all_meals(philos, args))
			;
	}
	return (NULL);
}
