/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:03 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 20:50:29 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static void pick_up_forks(t_philo *philo)
{
	if (philo->table->janitor->fork_indc[philo->first_fork])
		pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
	mtx_printf(philo->table, GREEN"has taken a fork", philo);
	if (philo->table->janitor->fork_indc[philo->second_fork])
		pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
	mtx_printf(philo->table, GREEN"has taken a fork", philo);
	mtx_printf(philo->table, BLUE"is eating", philo);
	philo->last_eat_t = get_time(philo->table->start_t);
	ft_usleep(philo->table->t_clock.eat_t, philo->table);
	pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
	philo->eat_count++;
	if (philo->eat_count >= philo->table->eat_goal)
		philo->state = satiated;
}

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->state = hungry;
	while (!philo->table->feast_famine)
		usleep(100);
	philo->last_eat_t = get_time(philo->table->start_t);// may need to be moved
	if (philo->seat_id % 2)
		ft_usleep(3, philo->table);
	while(philo->table->feast_famine)
	{
		pick_up_forks(philo);
		if (!philo->table->feast_famine)
			return (NULL);
		mtx_printf(philo->table, YELLOW"is sleeping", philo);
		ft_usleep(philo->table->t_clock.sleep_t, philo->table);
		if (!philo->table->feast_famine)
			return (NULL);
		mtx_printf(philo->table, PURPLE"is thinking", philo);
	}
	return (NULL);
}
