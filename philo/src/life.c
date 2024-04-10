/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:03:32 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/10 19:00:32 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// dont forget if number_win is defined
// careful lock a mutex that is already locked (same with unlocking)

void	ft_sleep(t_philo *philo, long time)
{
	if (philo->args->dead == 0)
	{
		philo_printf("is sleeping", philo, (t_args *)philo->args);
		ft_usleep(time);
	}
}

void	ft_eat(t_philo *philo, long time)
{
	if (philo->args->dead == 1)
		return ;
	pthread_mutex_lock(philo->fork_l);
	philo_printf("has taken a fork", philo, philo->args);
	pthread_mutex_lock(philo->fork_r);
	philo_printf("has taken a fork", philo, philo->args);
	pthread_mutex_lock(&philo->args->eat_lock);
	philo->is_eating = 1;
	ft_usleep(time);
	philo_printf("is eating", philo, philo->args);
	philo->meals++;
	pthread_mutex_unlock(&philo->args->eat_lock);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	philo->last_ate = get_time();
	philo->is_eating = 0;
}

void	ft_think(t_philo *philo)
{
	if (philo->args->dead == 0)
		philo_printf("is thinking", philo, (t_args *)philo->args);
}

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

void	*life(void *param)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)param;
	args = (t_args *)philo->args;
	philo->started = 1;
	while (args->all_started == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (not_dead(args))
	{
		ft_eat(philo, args->time_eat);
		ft_sleep(philo, args->time_sleep);
		ft_think(philo);
	}
	return (NULL);
}

// need to add the protections;
void	create_all_threads(t_philo *philos, t_args *args)
{
	pthread_t	watcher;
	short int	i;

	i = -1;
	pthread_create(&watcher, NULL, &watch_philos, philos);
	while (++i < args->n)
		pthread_create(&philos[i].thread, NULL, life, &philos[i]);
	// watch_philos(philos);
	pthread_join(watcher, NULL);
	i = -1;
	while (++i < args->n)
		pthread_join(philos[i].thread, NULL);
}
