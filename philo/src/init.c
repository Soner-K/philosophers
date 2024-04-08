/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:19:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/08 13:04:42 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// check what attribute to use for pthread_mutex_init


static void	init_mutex(t_args *args, pthread_mutex_t *forks)
{
	short int	i;

	i = -1;
	while (++i < args->n)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(args->write_lock, NULL);
	pthread_mutex_init(args->dead_lock, NULL);
	pthread_mutex_init(args->eat_lock, NULL);
}

void	init_philos(t_philo *philos, t_args *args, pthread_mutex_t *forks)
{
	short int	i;

	i = -1;
	init_mutex(args, forks);
	while (++i < args->n - 1)
	{
		philos[i].id = i + 1;
		philos[i].fork_r = &forks[i];
		philos[i].fork_l = &forks[i + 1];
	}
	philos[i].id = i + 1;
	philos[i].fork_l = philos[0].fork_r;
	philos[i].fork_r = philos[i - 1].fork_l;
	args->philos = philos;
}
