/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:57:18 by sokaraku          #+#    #+#             */
/*   Updated: 2024/04/02 10:15:07 by sokaraku         ###   ########.fr       */
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
	long	i;
	
	i = 0;
	(void)*param;
	printf("%d\n", 10 << 4);
	while (i < 10 << 4)
		i++;
	return (NULL);
}

int	main(void)
{
	// pthread_t thread;
	// pthread_t thread2;
	int *result;
	int *result2;

	result = NULL;
	result2 = NULL;
	// pthread_create(&thread, NULL, test3, result);
	// pthread_create(&thread2, NULL, test3, result2);
	test3(NULL);
	test3(NULL);
	// free((void *)&thread);
	// pthread_join(thread, (void **)&result);
	// pthread_join(thread2, (void **)&result2);
	// if (!result)
	// 	exit(EXIT_FAILURE);
	// for (int i = 0; i < 10000; i++)
	// 	printf("[%d]\n", result[i]);
	// for (int i = 0; i < 10000; i++)
	// 	printf("[%d]\n", result2[i]);
	// free(result);
	// free(result2);
}