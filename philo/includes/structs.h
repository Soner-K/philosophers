/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/06 17:36:43 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

/**
 * @brief Structure containing the arguments of the program.
 * @param optional A boolean taking the value 1 if number_win is defined,
 * and 0 otherwise.
 * @param dead A boolean taking the value 1 if a philosopher died.
 * @param n The number of philosophers.
 * @param time_die The maximum time a philosopher can go without eating.
 * @param time_eat The time it takes one philosopher to eat.
 * @param time_sleep The time a philospher takes to sleep.
 * @param number_win Optional parameter. The number of times each
 * philosopher need to eat to stop the simulation. If not defined,
 * the simulation goes on until one philosopher dies.
 */
typedef struct s_args
{
	char			optional;
	char			dead;
	int				n;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_win;
	long			last_meal;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*eat_lock;
}					t_args;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
	t_args			*args;
}					t_philo;

#endif