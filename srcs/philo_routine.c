/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:03 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/22 19:00:09 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->state = hungry;
	if (philo->seat_id % 2)
		usleep(30);
	philo->last_eat_t.tv_usec = philo->table->t_clock.start_t.tv_usec;//need to set this in waiter thread
	while(philo->table->feast_famine)// data race
	{
		pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
		pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
		philo->state = eating;
		usleep(philo->table->t_clock.eat_t.tv_usec);//what if a philo dies while eating?
		philo->eat_count++;
		pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
		philo->state = sleeping;
		usleep(philo->table->t_clock.sleep_t.tv_usec);//what if a philo dies while sleeping?
		philo->state = thinking;
		usleep(philo->table->t_clock.think_t.tv_usec);//what if a philo dies while thinking?
		if (philo->eat_count == philo->table->eat_goal)
			philo->state = satiated;
	}
}
