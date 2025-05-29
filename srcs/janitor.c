/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   janitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:22:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/29 20:35:01 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_cleanup(t_philo *philo)
{
	if (philo)
	{
		if (philo->thread_id)
			pthread_join(philo->thread_id, NULL);
		free(philo);
	}
	philo = NULL;
}

int	free_split(void **ptr, int end)
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

int	cleanup(t_table *table)
{
	int	i;

	if (!table)
		return (0);
	i = -1;
	while (++i < table->num_philos)
		if (table->seating_list[i])
			philo_cleanup(table->seating_list[i]);
	i = -1;
	while (++i < table->num_philos && table->num_philos != 1)
		if (table->janitor->fork_indc[i])
			pthread_mutex_destroy(&table->forks[i]);
	if (table->janitor->print_lock_indc)
		pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->seating_list);
	free(table->janitor->fork_indc);
	free(table->janitor);
	return (0);
}
