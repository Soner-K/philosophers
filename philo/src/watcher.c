/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:37:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/10 18:47:54 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	check_death_for_one(t_philo *philo, t_args *args)
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
		// pthread_mutex_lock(&args->write_lock);
		// printf("delay %ld last_ate %ld id %hd", delay, philo->last_ate, philo->id);
		// pthread_mutex_unlock(&args->write_lock);
		pthread_mutex_unlock(&args->eat_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&args->eat_lock);
	return (FALSE);
}

char	check_death_for_all(t_philo *philos, t_args *args)
{
	short int	i;

	i = -1;
	while (++i < args->n)
	{
		if (check_death_for_one(&philos[i], args) == TRUE)
		{
			args->dead = 1;
			philo_printf("died", &philos[i], args);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	*watch_philos(void *param)
{
	t_philo		*philos;
	t_args		*args;
	short int	i;

	philos = (t_philo *)param;
	args = (t_args *)philos->args;
	i = 0;
	while (i < args->n)
	{
		if (philos[i].started == 1)
			i++;
	}
	args->beginning_time = get_time();
	args->all_started = 1;
	while (check_death_for_all(philos, args) == FALSE)
		;
	return (NULL);
}
