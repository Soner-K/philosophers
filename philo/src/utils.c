/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:28:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/15 19:32:18 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	ft_usleep(long mls, t_args *args)
{
	// long	beginning;

	if (!not_dead(args))
		return ;
	// // pthread_mutex_lock(&args->dead_lock);
	// // if (args->dead == 1)
	// // 	return ;
	// // pthread_mutex_unlock(&args->dead_lock);
	// beginning = get_time();
	// while ((get_time() - beginning) < mls)
	// 	usleep(500);
	usleep(mls * 1000);
}

void	philo_printf(char *message, t_philo *philo, t_args *args, char force)
{
	long		time;
	static char	i;

	if (!not_dead(args) && force == 0)
		return ;
	if (args->all_ate == 1 && i == 1)
		return ;
	if (args->all_ate == 1)
		i = 1;
	time = get_time();
	pthread_mutex_lock(&args->access_lock);
	if (args->beginning_time == 0)
		time = 0;
	else
		time -= args->beginning_time;
	pthread_mutex_unlock(&args->access_lock);
	pthread_mutex_lock(&args->write_lock);
	printf("%s%ld%s %d %s\n", YELLOW, time, NO_COLOR, philo->id, message);
	pthread_mutex_unlock(&args->write_lock);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
