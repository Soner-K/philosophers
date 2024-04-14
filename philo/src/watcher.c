/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:37:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/14 19:10:25 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	death_one(t_philo *philo, t_args *args)
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

char	death_all(t_philo *philos, t_args *args)
{
	short int	i;

	i = -1;
	while (++i < args->n)
	{
		if (death_one(&philos[i], args) == TRUE)
		{
			args->dead = 1;
			philo_printf("died", &philos[i], args, 1);
			return (TRUE);
		}
	}
	return (FALSE);
}

char	all_meals(t_philo *philos, t_args *args)
{
	short int	i;
	int			finished;

	i = -1;
	finished = 0;
	while (++i < args->n)
	{
		// printf("meals philos[%d] %d\n", philos[i].id, philos[i].meals);
		if (philos[i].meals >= args->number_win)
			finished++;
		else
			break ;
	}
	if (finished >= args->n)
		return (args->all_ate = 1, TRUE);
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
