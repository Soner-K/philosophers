/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:03:32 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/15 19:31:27 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_philo *philo)
{
	philo_printf("is thinking", philo, (t_args *)philo->args, 0);
}

void	ft_sleep(t_philo *philo, long time)
{
	philo_printf("is sleeping", philo, (t_args *)philo->args, 0);
	ft_usleep(time, philo->args);
	ft_think(philo);
	if (philo->args->n % 2)
	{
		ft_usleep(philo->args->time_eat * 2 - philo->args->time_sleep,
			philo->args);
	}
}

void	ft_eat_even(t_philo *philo, long time)
{
	pthread_mutex_lock(philo->fork_r);
	philo_printf("has taken a fork", philo, philo->args, 0);
	if (philo->args->n == 1)
	{
		ft_usleep(philo->args->time_die, philo->args);
		return ;
	}
	pthread_mutex_lock(philo->fork_l);
	philo_printf("has taken a fork", philo, philo->args, 0);
	philo->is_eating = 1;
	philo_printf("is eating", philo, philo->args, 0);
	pthread_mutex_lock(&philo->args->eat_lock);
	philo->meals++;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->args->eat_lock);
	ft_usleep(time, philo->args);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	ft_eat_odd(t_philo *philo, long time)
{
	pthread_mutex_lock(philo->fork_l);
	philo_printf("has taken a fork", philo, philo->args, 0);
	if (philo->args->n == 1)
	{
		ft_usleep(philo->args->time_die, philo->args);
		return ;
	}
	pthread_mutex_lock(philo->fork_r);
	philo_printf("has taken a fork", philo, philo->args, 0);
	philo->is_eating = 1;
	philo_printf("is eating", philo, philo->args, 0);
	pthread_mutex_lock(&philo->args->eat_lock);
	philo->meals++;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->args->eat_lock);
	ft_usleep(time, philo->args);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
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
	if (philo->id % 2 == 0)
		ft_usleep(1, args);
	while (not_dead(args))
	{
		if (args->all_ate == 1)
			break ;
		if (philo->id % 2 == 0 || args->n == 1)
			ft_eat_even(philo, args->time_eat);
		else if (philo->id % 2 == 1)
			ft_eat_odd(philo, args->time_eat);
		ft_sleep(philo, args->time_sleep);
	}
	return (NULL);
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
