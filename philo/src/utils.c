/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:28:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/10 17:18:51 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	ft_usleep(long mls)
{
	long	beginning;

	beginning = get_time();
	while ((get_time() - beginning) < mls)
		usleep(500);
}

// void	ft_usleep(long mls)
// {
// 	long	to_sleep;

// 	to_sleep = mls * 1000;
// 	if (to_sleep > UINT_MAX)
// 		return ;
// 	usleep(to_sleep);
// }

void	philo_printf(char *message, t_philo *philo, t_args *args)
{
	long	time;

	// if (args->dead == 1)
	// 	return ;
	time = get_time();
	time -= args->beginning_time;;
	pthread_mutex_lock(&args->write_lock);
	printf("%s[%ld]%s %d %s\n", YELLOW, time, NO_COLOR, philo->id, message);
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

// size_t	get_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }