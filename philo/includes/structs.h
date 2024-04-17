/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:53:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/16 15:31:52 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

typedef struct s_args	t_args;

/**
 * @brief Structure containing all the needed infos for a philosopher.
 * @param last_ate The time when a philosopher last ate.
 * @param meals The number of meals a philosopher ate.
 * @param id Philosopher's id.
 * @param thread Philosopher's thread. 
 * @param fork_l A mutex representing the left fork of a philosopher.
 * @param fork_r A mutex representing the right fork of a philosopher.
 * @param args A pointer to the args' structure.
 */
typedef struct s_philo
{
	long			last_ate;
	int				meals;
	short int		id;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	t_args			*args;
}					t_philo;

/**
 * @brief Structure containing all the variables needed for the program.
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
 * @param beginning_time The time at which the philosophers started to eat.
 * @param write_lock A mutex for writing to the terminal.
 * @param dead_lock A mutex to announce the death of a philosopher.
 * @param eat_lock A mutex to announce that a philosopher is eating.
 * @param access_lock A mutex for modifying values.
 * @param forks A pointer to a dynamically allocated array
 * containing all the mutexes for the forks.
 * @param philos A pointer to an array on the stack, containing
 * all the philosophers' structures.
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
	long			beginning_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	access_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_args;

#endif