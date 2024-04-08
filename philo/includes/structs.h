/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/08 13:04:07 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

typedef struct s_philo
{
	short int		id;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	void			*args;
}					t_philo;

/**
 * @brief Structure containing the arguments of the program.
 * @param optional A boolean taking the value 1 if number_win is defined,
 * and 0 otherwise.
 * @param dead A boolean taking the value 1 if a philosopher died.
 * @param n The number of philosophers.
 * @param time_die The maximum time a philosopher can go without eating
 * (in milliseconds).
 * @param time_eat The time it takes one philosopher to eat (in milliseconds).
 * @param time_sleep The time a philospher takes to sleep (in milliseconds).
 * @param number_win Optional parameter. The number of times each
 * philosopher need to eat to stop the simulation. If not defined,
 * the simulation goes on until one philosopher dies.
 * @param last_meal The time at which a philosopher had his last meal.
 * @param write_lock A mutex for writing to the terminal.
 * @param dead_lock A mutex to announce the death of a philosopher.
 * @param eat_lock A mutex to announce that a philosopher is eating.
 * @param forks A pointer to an array on the stack, containing all the mutexes
 * for the forks.
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
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_args;


#endif