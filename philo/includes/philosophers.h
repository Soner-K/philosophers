/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:56:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/09 15:32:41 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libs.h"

void	do_threads(void *(f)(void *), void *arg, void *ret,
			pthread_t threads[]);
void	write_error(char *str);
char	check_input(int ac, char **argv, t_args *args);
void	init_philos(t_philo *philos, t_args *args, pthread_mutex_t *forks);
void	do_routine(t_philo *philos, t_args *args);
void	ft_usleep(unsigned int seconds);
void	philo_printf(char *message, t_philo *philo, t_args *args);
long	get_time(void);
void	*watch_philos(void *param);
void	create_all_threads(t_philo *philos, t_args *args);
#endif