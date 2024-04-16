/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:11:59 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/16 15:00:35 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutex_destroy(pthread_mutex_t *forks, t_args *args)
{
	int	i;

	i = 0;
	while (args->n--)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->access_lock);
	pthread_mutex_destroy(&args->eat_lock);
	pthread_mutex_destroy(&args->write_lock);
	pthread_mutex_destroy(&args->dead_lock);
}

void	create_all_threads(t_philo *philos, t_args *args)
{
	pthread_t	watcher;
	short int	i;

	i = -1;
	if (pthread_create(&watcher, NULL, &watch_philos, philos) != 0)
		return (write_error("Error\nIssue with thread creation"));
	while (++i < args->n)
	{
		if (pthread_create(&philos[i].thread, NULL, life, &philos[i]) != 0)
			return (write_error("Error\nIssue with thread creation"));
	}
	if (pthread_join(watcher, NULL) != 0)
		return (write_error("Error\nIssue with thread joining"));
	i = -1;
	while (++i < args->n)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (write_error("Error\nIssue with thread joining"));
	}
}

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			philos[200];
	pthread_mutex_t	*forks;

	if (ac < 4)
		return (write_error("Error\nWrong number of arguments"), -1);
	if (check_input(ac, av, &args) == 0)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * 200);
	if (!forks)
		return (write_error("Error\nAllocation issue."), -1);
	init_philos(philos, &args, forks);
	create_all_threads(philos, &args);
	mutex_destroy(forks, &args);
	free(forks);
}
