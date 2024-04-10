/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:57:18 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/10 13:10:02 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test(void *param)
{
	int	*val;

	val = (int *)param;
	*val = 5;
	return (val);
}

void	*test2(void *param)
{
	int	*tab;
	int	i;

	(void)*param;
	i = -1;
	tab = malloc(sizeof(int) * 10000);
	if (!tab)
		return (NULL);
	while (++i < 10000)
		tab[i] = i;
	return (tab);
}

void	*test3(void *param)
{
	t_training	*t;
	int			j;

	t = (t_training *)param;
	j = 0;
	while (j++ < 1L << 16)
	{
		pthread_mutex_lock(&t->mutex);
		t->i++;
		pthread_mutex_unlock(&t->mutex);
	}
	return (NULL);
}

// int	main(void) // race condition test 3
// {
// 	pthread_t thread;
// 	pthread_t thread2;
// 	t_training utils;

// 	utils.i = 0;
// 	pthread_mutex_init(&utils.mutex, NULL);
// 	pthread_create(&thread, NULL, test3, &utils);
// 	pthread_create(&thread2, NULL, test3, &utils);
// 	test3(&utils);
// 	pthread_join(thread, NULL);
// 	pthread_join(thread2, NULL);
// 	printf("%d\n", utils.i);
// 	pthread_mutex_destroy(&utils.mutex);
// }

void	*test4(void *param)
{
	int	*n;

	n = (int *)param;
	if (*n == 4)
		(*n) /= 2;
	else
		(*n) /= 2;
	return (n);
}

void	*test5(void *param)
{
	static int	tab[10000];
	static int	i;
	int			j;
	t_training	t;

	t = *(t_training *)param;
	j = -1;
	pthread_mutex_lock(&t.mutex);
	if (i == 0)
		while (++j < 100)
			tab[j] = j;
	printf("[%d]\n", tab[i++]);
	pthread_mutex_unlock(&t.mutex);
	return (NULL);
}

// int	main(void) //test 5
// {
// 	pthread_t	threads[NB_THREAD];
// 	t_training	utils;
// 	int			i;

// 	utils.i = 0;
// 	i = 0;
// 	while (i++ < 100)
// 		utils.tab[i] = i;
// 	pthread_mutex_init(&utils.mutex, NULL);
// 	while (i++ < 10)
// 		do_threads(test5, &utils, NULL, threads);
// 	pthread_mutex_destroy(&utils.mutex);
// }

// void	*test6(void *param)
// {
// 	printf("[%d] \n", *(int *)param);
// 	return (NULL);
// }

// int	main(void) //test6
// {
// 	pthread_t	threads[100];
// 	int			i;
// 	int			tab[100];

// 	i = -1;
// 	while (++i < 100)
// 		tab[i] = i;
// 	i = -1;
// 	while (++i < 100)
// 		pthread_create(&threads[i], NULL, test6, tab + i);
// 	i = -1;
// 	while (++i < 100)
// 		pthread_join(threads[i], NULL);
// }

// int	main(void)
// {
// 	struct timeval start;
// 	struct timeval end;
// 	long elapsed_time;

// 	gettimeofday(&start, NULL);
// 	for (long i = 0; i < 1L << 32; i++)
// 		;
// 	gettimeofday(&end, NULL);
// 	printf("%ld\n", start.tv_sec);
// 	printf("%ld\n", end.tv_sec);
// 	printf("%ld\n", start.tv_usec);
// 	printf("%ld\n", end.tv_usec);
// 	elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec
// 			- start.tv_usec);
// 	printf("Elapsed time: %ld microseconds\n", elapsed_time);
// }

// void	mutex_destroy(pthread_mutex_t *forks, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (n--)
// 	{
// 		pthread_mutex_destroy(&forks[i]);
// 		i++;
// 	}
// }

int main(int ac, char **av)
{
	t_args	args;
	t_philo	philos[200];
	pthread_mutex_t	forks[200];
	int		i;

	if (ac < 4)
		return (0);
	i = 0;
	if (check_input(ac, av, &args) == 0)
		return (0);
	init_philos(philos, &args, forks);
	// printf("IN MAIN\n");
	// while (i < args.n)
	// {
	// 	printf("philos[%d].id = %d\n", i, philos[i].id);
	// 	printf("philos[%d].fork_l = %p\n", i, (void *) philos[i].fork_l);
	// 	printf("philos[%d].fork_r = %p\n\n\n", i, (void *) philos[i].fork_r);
	// 	i++;
	// }
	// do_routine(philos, &args);
	create_all_threads(philos, &args);
	// mutex_destroy(args.forks, args.n);
	// free(args.forks);
}

// int main(void)
// {
// 	usleep(1000000);
// }