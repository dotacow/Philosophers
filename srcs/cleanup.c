/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:22:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/22 15:49:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"
#include <pthread.h>


void philo_cleanup(t_philo *philo)
{
	if (philo)
	{
		if (philo->thread_id)
			pthread_join(philo->thread_id, NULL);
		free(philo);
	}
	philo = NULL;
}


int free_split(void **ptr, int end)
{
	int	i;

	if (!ptr)
		return (0);
	i = 0;
	while (i < end)
	{
		if (ptr[i])
			free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return (0);
}

int cleanup(t_table *table)
{
	int	i;

	if (!table)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		if (&table->forks[i])
			pthread_mutex_destroy(&table->forks[i]);
		if (table->seating_list[i])
			philo_cleanup(table->seating_list[i++]);
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->seating_list);
	free(table);
	table = NULL;
	return (0);
}
