/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/03 17:58:36 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

/**
 * @brief Structure containing the arguments of the program.
 * @param n The number of philosophers.
 * @param time_die The maximum time a philosopher can go without eating.
 * @param time_eat The time it takes one philosopher to eat.
 * @param time_sleep The time a philospher takes to sleep.
 * @param number_win Optional parameter. The number of times each
 * philosopher need to eat to stop the simulation. If not defined,
 * the simulation goes on until one philosopher dies.
 * @param optional A boolean taking the value 1 if number_win is defined,
 * and 0 otherwise.
 */
typedef struct s_args
{
	int		n;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		number_win;
	char	optional;
}			t_args;

typedef struct s_philo
{
	pthread_t	thread;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	
}

#endif