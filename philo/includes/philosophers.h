/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:56:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/08 14:18:09 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libs.h"

void	do_threads(void *(f)(void *), void *arg, void *ret,
			pthread_t threads[]);
void	write_error(char *str);
char	check_input(int ac, char **argv, t_args *args);
void	init_philo_array(t_philo philos[200], t_args *args);
void	do_routine(t_philo *philos, t_args *args);
#endif