/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:28:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/14 19:01:50 by sokaraku         ###   ########.fr       */
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
	long	beginning;

	if (args->dead == 1)
		return ;
	beginning = get_time();
	while ((get_time() - beginning) < mls)
		usleep(500);
}

void	ft_usleep2(long mls)
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

void	philo_printf(char *message, t_philo *philo, t_args *args, char force)
{
	long		time;
	static char	i;
	// (void)message;
	// (void)philo;
	if ((args->dead == 1 && force == 0) || (args->all_ate == 1 && i == 1))
		return ;
	if (args->all_ate == 1)
		i = 1;
	time = get_time();
	time -= args->beginning_time;
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