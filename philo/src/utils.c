/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:28:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/09 13:34:05 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_threads(void *(f)(void *), void *arg, void *ret, pthread_t threads[])
{
	int			i;

	i = -1;
	while (++i < NB_THREAD)
		pthread_create(&threads[i], NULL, f, arg);
	i = -1;
	while (++i < NB_THREAD)
		pthread_join(threads[i], &ret);
}

void	write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	ft_usleep(unsigned int seconds)
{
	long	to_sleep;

	to_sleep = seconds * 1000;
	if (to_sleep > UINT_MAX)
		return ;
	usleep(to_sleep);
}

void	philo_printf(char *message, t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&args->write_lock);
	printf("%d %s\n", philo->id, message);
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
