/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:37:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/09 16:50:50 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	check_death_for_one(t_philo *philo, t_args *args)
{
	long	current_time;
	long	delay;

	current_time = get_time();
	delay = current_time - philo->last_ate;
	if (delay >= args->time_die && philo->is_eating == 0)
		return (TRUE);
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

void	*watch_philos(void	*param)
{
	t_philo	*philos;
	t_args	*args;

	philos = (t_philo *)param;
	args = (t_args *)philos->args;
	while (check_death_for_all(philos, args) == FALSE)
		;
	return (NULL);
}
