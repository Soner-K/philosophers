/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:56:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/16 15:18:15 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libs.h"

void	init_philos(t_philo *philos, t_args *args, pthread_mutex_t *forks);

char	not_dead(t_args *args);
void	*life(void *param);

void	create_all_threads(t_philo *philos, t_args *args);

char	check_input(int ac, char **argv, t_args *args);

void	write_error(char *str);
void	ft_usleep(long mls, t_args *args);
void	philo_printf(char *message, t_philo *philo, t_args *args, char force);
long	get_time(void);

void	*watch_philos(void *param);
#endif