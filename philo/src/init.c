/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:19:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/06 18:36:19 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// check what attribute to use for pthread_mutex_init
// careful not to destroy the same mutex multiple times with the mutex_destroy.
void	init_fork(t_philo *philos, t_args *args, int index)
{
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	int				i;

	(void)args;
	if (index % 2)
		pthread_mutex_init(&fork_l, NULL);
	else
		pthread_mutex_init(&fork_r, NULL);
	i = index;
	// (philos[index]).id = index + 1;
	// printf("%d\n", (philos[index]).id);
	philos[index].fork_l = fork_l;
	philos[index].fork_r = fork_r;
	if (index + 1 < args->n)
		philos[index + 1].fork_r = fork_l;
	if (index - 1 == -1)
		index = args->n;
	philos[index - 1].fork_l = fork_r;
	if (index == 3)
	{
		printf("philos[%d].fork_l = %p\n", 0, &philos[0].fork_l);
		printf("philos[%d].fork_r = %p\n\n\n", 0, &philos[0].fork_r);
		printf("philos[%d].fork_l = %p\n", 1, &philos[1].fork_l);
		printf("philos[%d].fork_r = %p\n\n\n", 1, &philos[1].fork_r);
		printf("philos[%d].fork_l = %p\n", 2, &philos[2].fork_l);
		printf("philos[%d].fork_r = %p\n\n\n", 2, &philos[2].fork_r);
	}
}

void	init_philo_array(t_philo philos[200], t_args *args)
{
	pthread_mutex_t forks[200];
	int i;

	i = -1;
	while (++i < args->n)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < args->n)
	{
		philos[i].fork_l = forks[i];
	}
}

void	init_philo_array(t_philo philos[200], t_args *args)
{
	int i;

	i = -1;
	while (++i < args->n)
		init_fork(philos, args, i);
}