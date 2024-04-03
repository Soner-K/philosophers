/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:28:15 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/03 15:58:19 by sokaraku         ###   ########.fr       */
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
